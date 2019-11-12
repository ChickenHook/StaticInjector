
#include <stdio.h>

#include <chickenHook/hooking.h>
#include <chickenHook/logging.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/mman.h>


#define gettid() syscall(SYS_gettid)


bool updatePermissions(void *addr, int permissions) {
    size_t pagesize = (size_t) sysconf(_SC_PAGESIZE);
    void *lowerBoundary = (void *) ((long long) addr - ((long long) addr % pagesize));

    if (mprotect(lowerBoundary, pagesize, permissions) != 0) {
        return false;
    }
    return true;
}


void logCallback(const std::string logtext) {

    printf("%s\n", logtext.c_str());

}

template<class Elem, class Traits>
static inline void
hex_dump(const void *aData, std::size_t aLength, std::basic_ostream <Elem, Traits> &aStream,
         std::size_t aWidth = 16) {
    const char *const start = static_cast<const char *>(aData);
    const char *const end = start + aLength;
    const char *line = start;
    while (line != end) {
        aStream.width(4);
        aStream.fill('0');
        aStream << std::hex << line - start << " : ";
        std::size_t lineLength = std::min(aWidth, static_cast<std::size_t>(end - line));
        for (std::size_t pass = 1; pass <= 2; ++pass) {
            for (const char *next = line; next != end && next != line + aWidth; ++next) {
                char ch = *next;
                switch (pass) {
                    case 1:
                        aStream << (ch < 32 ? '.' : ch);
                        break;
                    case 2:
                        if (next != line)
                            aStream << " ";
                        aStream.width(2);
                        aStream.fill('0');
                        aStream << std::hex << std::uppercase
                                << static_cast<int>(static_cast<unsigned char>(ch));
                        break;
                }
            }
            if (pass == 1 && lineLength != aWidth)
                aStream << std::string(aWidth - lineLength, ' ');
            aStream << " ";
        }
        aStream << std::endl;
        line = line + lineLength;
    }
}

ssize_t my_read(int __fd, void *__buf, size_t __count) {
    //printf("read called [-] %d", __fd);
    int res = -1;
    ChickenHook::Trampoline trampoline;
    if (ChickenHook::Hooking::getInstance().getTrampolineByAddr((void *) &read, trampoline)) {
        //printf("hooked function call original function");
        // printLines(hexdump(static_cast<const uint8_t *>(__buf), __count, "read"));
        trampoline.copyOriginal();
        res = read(__fd, __buf, __count);
        trampoline.reinstall();
        hex_dump(__buf, __count, std::cout);
        return res;
    } else {
        printf("hooked function cannot call original function");
    }
    return res;
}

char *my_strcpy(char *__dst, const char *__src) {
    printf("strcpy called [-] ");
    hex_dump(__src, strlen(__src), std::cout);
    char *res = nullptr;
    ChickenHook::Trampoline trampoline;
    if (ChickenHook::Hooking::getInstance().getTrampolineByAddr((void *) &strcpy, trampoline)) {
        printf("hooked function call original function");
        // printLines(hexdump(static_cast<const uint8_t *>(__buf), __count, "read"));
        trampoline.copyOriginal();
        res = strcpy(__dst, __src);
        trampoline.reinstall();
        return res;
    } else {
        printf("hooked function cannot call original function");
    }
    return res;
}

int my_open(const char *__path, int __flags, ...) {
    printf("open called [-] %s\n", __path);

    int res = -1;
    ChickenHook::Trampoline trampoline;
    if (ChickenHook::Hooking::getInstance().getTrampolineByAddr((void *) &open, trampoline)) {
        printf("hooked function call original function\n");

        trampoline.copyOriginal();
        res = open(__path, __flags);
        trampoline.reinstall();
        return res;
    } else {
        printf("hooked function cannot call original function\n");
    }
    return -1;
}


pthread_t hooksInstallThread;

void installWithThread();


void pseudoSleep(int iterations) {
    for (int i = 0; i < gettid() * iterations;) {
        i++;
    }
}

void *installHooks(void *) { // install hooks only once!
    char *hinit = getenv("HINIT");
    printf("installHooks <%ld> <%s>\n", gettid(), hinit);
    //usleep(gettid());
    //pseudoSleep(100);

    if (hinit == nullptr) {
        putenv("HINIT=true");

        printf("Waiting for hooks... \n");
        //sleep(1);
        usleep(20 * 1000 * 1000);
        //usleep(5*1000 * 1000);
        printf("Started install hooks\n");
        ChickenHook::Hooking::getInstance().setLoggingCallback(&logCallback);
        printf("Using chickenhook instance <%p>\n", &ChickenHook::Hooking::getInstance());
        ChickenHook::Hooking::getInstance().hook((void *) &read, (void *) &my_read);

        //ChickenHook::Hooking::getInstance().hook((void *) &strcpy, (void *) &my_strcpy);
        //ChickenHook::Hooking::getInstance().hook((void *) &open, (void *) &my_open);
        printf("Install hooks finished\n");/**/

    }

    return nullptr;
}

void installWithThread() {
    if (pthread_create(&hooksInstallThread, NULL, &installHooks, nullptr)) {
        printf("Error creating hooking thread!");
    }
}

void __attribute__  ((constructor (102))) testInit() {
    printf("You are hacked %ld\n", gettid());
    //pseudoSleep(100);
    installWithThread();
    //installHooks(nullptr);
}