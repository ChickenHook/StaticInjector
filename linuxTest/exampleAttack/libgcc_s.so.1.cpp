#include <string>
#include <unistd.h>
#include <dlfcn.h>

#include "symbolhook.h"

void *handle;

void funA() {
    printf("ERROR, THIS SHOULD NEVER APPEAR\n");
}
extern "C" __attribute__((used)) void *p__Unwind_Backtrace = (void *) funA;
extern "C" void _Unwind_Backtrace() {
    SYMBOL_HOOK( p__Unwind_Backtrace);
}
extern "C" __attribute__((used)) void *p__Unwind_DeleteException = (void *) funA;
extern "C" void _Unwind_DeleteException() {
    SYMBOL_HOOK( p__Unwind_DeleteException);
}
extern "C" __attribute__((used)) void *p__Unwind_FindEnclosingFunction = (void *) funA;
extern "C" void _Unwind_FindEnclosingFunction() {
    SYMBOL_HOOK( p__Unwind_FindEnclosingFunction);
}
extern "C" __attribute__((used)) void *p__Unwind_Find_FDE = (void *) funA;
extern "C" void _Unwind_Find_FDE() {
    SYMBOL_HOOK( p__Unwind_Find_FDE);
}
extern "C" __attribute__((used)) void *p__Unwind_ForcedUnwind = (void *) funA;
extern "C" void _Unwind_ForcedUnwind() {
    SYMBOL_HOOK( p__Unwind_ForcedUnwind);
}
extern "C" __attribute__((used)) void *p__Unwind_GetCFA = (void *) funA;
extern "C" void _Unwind_GetCFA() {
    SYMBOL_HOOK( p__Unwind_GetCFA);
}
extern "C" __attribute__((used)) void *p__Unwind_GetDataRelBase = (void *) funA;
extern "C" void _Unwind_GetDataRelBase() {
    SYMBOL_HOOK( p__Unwind_GetDataRelBase);
}
extern "C" __attribute__((used)) void *p__Unwind_GetGR = (void *) funA;
extern "C" void _Unwind_GetGR() {
    SYMBOL_HOOK( p__Unwind_GetGR);
}
extern "C" __attribute__((used)) void *p__Unwind_GetIP = (void *) funA;
extern "C" void _Unwind_GetIP() {
    SYMBOL_HOOK( p__Unwind_GetIP);
}
extern "C" __attribute__((used)) void *p__Unwind_GetIPInfo = (void *) funA;
extern "C" void _Unwind_GetIPInfo() {
    SYMBOL_HOOK( p__Unwind_GetIPInfo);
}
extern "C" __attribute__((used)) void *p__Unwind_GetLanguageSpecificData = (void *) funA;
extern "C" void _Unwind_GetLanguageSpecificData() {
    SYMBOL_HOOK( p__Unwind_GetLanguageSpecificData);
}
extern "C" __attribute__((used)) void *p__Unwind_GetRegionStart = (void *) funA;
extern "C" void _Unwind_GetRegionStart() {
    SYMBOL_HOOK( p__Unwind_GetRegionStart);
}
extern "C" __attribute__((used)) void *p__Unwind_GetTextRelBase = (void *) funA;
extern "C" void _Unwind_GetTextRelBase() {
    SYMBOL_HOOK( p__Unwind_GetTextRelBase);
}
extern "C" __attribute__((used)) void *p__Unwind_RaiseException = (void *) funA;
extern "C" void _Unwind_RaiseException() {
    SYMBOL_HOOK( p__Unwind_RaiseException);
}
extern "C" __attribute__((used)) void *p__Unwind_Resume = (void *) funA;
extern "C" void _Unwind_Resume() {
    SYMBOL_HOOK( p__Unwind_Resume);
}
extern "C" __attribute__((used)) void *p__Unwind_Resume_or_Rethrow = (void *) funA;
extern "C" void _Unwind_Resume_or_Rethrow() {
    SYMBOL_HOOK( p__Unwind_Resume_or_Rethrow);
}
extern "C" __attribute__((used)) void *p__Unwind_SetGR = (void *) funA;
extern "C" void _Unwind_SetGR() {
    SYMBOL_HOOK( p__Unwind_SetGR);
}
extern "C" __attribute__((used)) void *p__Unwind_SetIP = (void *) funA;
extern "C" void _Unwind_SetIP() {
    SYMBOL_HOOK( p__Unwind_SetIP);
}
extern "C" __attribute__((used)) void *p___absvdi2 = (void *) funA;
extern "C" void __absvdi2() {
    SYMBOL_HOOK( p___absvdi2);
}
extern "C" __attribute__((used)) void *p___absvsi2 = (void *) funA;
extern "C" void __absvsi2() {
    SYMBOL_HOOK( p___absvsi2);
}
extern "C" __attribute__((used)) void *p___absvti2 = (void *) funA;
extern "C" void __absvti2() {
    SYMBOL_HOOK( p___absvti2);
}
extern "C" __attribute__((used)) void *p___addtf3 = (void *) funA;
extern "C" void __addtf3() {
    SYMBOL_HOOK( p___addtf3);
}
extern "C" __attribute__((used)) void *p___addvdi3 = (void *) funA;
extern "C" void __addvdi3() {
    SYMBOL_HOOK( p___addvdi3);
}
extern "C" __attribute__((used)) void *p___addvsi3 = (void *) funA;
extern "C" void __addvsi3() {
    SYMBOL_HOOK( p___addvsi3);
}
extern "C" __attribute__((used)) void *p___addvti3 = (void *) funA;
extern "C" void __addvti3() {
    SYMBOL_HOOK( p___addvti3);
}
extern "C" __attribute__((used)) void *p___ashlti3 = (void *) funA;
extern "C" void __ashlti3() {
    SYMBOL_HOOK( p___ashlti3);
}
extern "C" __attribute__((used)) void *p___ashrti3 = (void *) funA;
extern "C" void __ashrti3() {
    SYMBOL_HOOK( p___ashrti3);
}
extern "C" __attribute__((used)) void *p___bswapdi2 = (void *) funA;
extern "C" void __bswapdi2() {
    SYMBOL_HOOK( p___bswapdi2);
}
extern "C" __attribute__((used)) void *p___bswapsi2 = (void *) funA;
extern "C" void __bswapsi2() {
    SYMBOL_HOOK( p___bswapsi2);
}
extern "C" __attribute__((used)) void *p___clear_cache = (void *) funA;
extern "C" void __clear_cache() {
    SYMBOL_HOOK( p___clear_cache);
}
extern "C" __attribute__((used)) void *p___clrsbdi2 = (void *) funA;
extern "C" void __clrsbdi2() {
    SYMBOL_HOOK( p___clrsbdi2);
}
extern "C" __attribute__((used)) void *p___clrsbti2 = (void *) funA;
extern "C" void __clrsbti2() {
    SYMBOL_HOOK( p___clrsbti2);
}
extern "C" __attribute__((used)) void *p___clzdi2 = (void *) funA;
extern "C" void __clzdi2() {
    SYMBOL_HOOK( p___clzdi2);
}
extern "C" __attribute__((used)) void *p___clzti2 = (void *) funA;
extern "C" void __clzti2() {
    SYMBOL_HOOK( p___clzti2);
}
extern "C" __attribute__((used)) void *p___cmpti2 = (void *) funA;
extern "C" void __cmpti2() {
    SYMBOL_HOOK( p___cmpti2);
}
extern "C" __attribute__((used)) void *p___cpu_indicator_init = (void *) funA;
extern "C" void __cpu_indicator_init() {
    SYMBOL_HOOK( p___cpu_indicator_init);
}
extern "C" __attribute__((used)) void *p___ctzdi2 = (void *) funA;
extern "C" void __ctzdi2() {
    SYMBOL_HOOK( p___ctzdi2);
}
extern "C" __attribute__((used)) void *p___ctzti2 = (void *) funA;
extern "C" void __ctzti2() {
    SYMBOL_HOOK( p___ctzti2);
}
extern "C" __attribute__((used)) void *p___deregister_frame = (void *) funA;
extern "C" void __deregister_frame() {
    SYMBOL_HOOK( p___deregister_frame);
}
extern "C" __attribute__((used)) void *p___deregister_frame_info = (void *) funA;
extern "C" void __deregister_frame_info() {
    SYMBOL_HOOK( p___deregister_frame_info);
}
extern "C" __attribute__((used)) void *p___deregister_frame_info_bases = (void *) funA;
extern "C" void __deregister_frame_info_bases() {
    SYMBOL_HOOK( p___deregister_frame_info_bases);
}
extern "C" __attribute__((used)) void *p___divdc3 = (void *) funA;
extern "C" void __divdc3() {
    SYMBOL_HOOK( p___divdc3);
}
extern "C" __attribute__((used)) void *p___divmodti4 = (void *) funA;
extern "C" void __divmodti4() {
    SYMBOL_HOOK( p___divmodti4);
}
extern "C" __attribute__((used)) void *p___divsc3 = (void *) funA;
extern "C" void __divsc3() {
    SYMBOL_HOOK( p___divsc3);
}
extern "C" __attribute__((used)) void *p___divtc3 = (void *) funA;
extern "C" void __divtc3() {
    SYMBOL_HOOK( p___divtc3);
}
extern "C" __attribute__((used)) void *p___divtf3 = (void *) funA;
extern "C" void __divtf3() {
    SYMBOL_HOOK( p___divtf3);
}
extern "C" __attribute__((used)) void *p___divti3 = (void *) funA;
extern "C" void __divti3() {
    SYMBOL_HOOK( p___divti3);
}
extern "C" __attribute__((used)) void *p___divxc3 = (void *) funA;
extern "C" void __divxc3() {
    SYMBOL_HOOK( p___divxc3);
}
extern "C" __attribute__((used)) void *p___emutls_get_address = (void *) funA;
extern "C" void __emutls_get_address() {
    SYMBOL_HOOK( p___emutls_get_address);
}
extern "C" __attribute__((used)) void *p___emutls_register_common = (void *) funA;
extern "C" void __emutls_register_common() {
    SYMBOL_HOOK( p___emutls_register_common);
}
extern "C" __attribute__((used)) void *p___enable_execute_stack = (void *) funA;
extern "C" void __enable_execute_stack() {
    SYMBOL_HOOK( p___enable_execute_stack);
}
extern "C" __attribute__((used)) void *p___eqtf2 = (void *) funA;
extern "C" void __eqtf2() {
    SYMBOL_HOOK( p___eqtf2);
}
extern "C" __attribute__((used)) void *p___extenddftf2 = (void *) funA;
extern "C" void __extenddftf2() {
    SYMBOL_HOOK( p___extenddftf2);
}
extern "C" __attribute__((used)) void *p___extendsftf2 = (void *) funA;
extern "C" void __extendsftf2() {
    SYMBOL_HOOK( p___extendsftf2);
}
extern "C" __attribute__((used)) void *p___extendxftf2 = (void *) funA;
extern "C" void __extendxftf2() {
    SYMBOL_HOOK( p___extendxftf2);
}
extern "C" __attribute__((used)) void *p___ffsdi2 = (void *) funA;
extern "C" void __ffsdi2() {
    SYMBOL_HOOK( p___ffsdi2);
}
extern "C" __attribute__((used)) void *p___ffsti2 = (void *) funA;
extern "C" void __ffsti2() {
    SYMBOL_HOOK( p___ffsti2);
}
extern "C" __attribute__((used)) void *p___fixdfti = (void *) funA;
extern "C" void __fixdfti() {
    SYMBOL_HOOK( p___fixdfti);
}
extern "C" __attribute__((used)) void *p___fixsfti = (void *) funA;
extern "C" void __fixsfti() {
    SYMBOL_HOOK( p___fixsfti);
}
extern "C" __attribute__((used)) void *p___fixtfdi = (void *) funA;
extern "C" void __fixtfdi() {
    SYMBOL_HOOK( p___fixtfdi);
}
extern "C" __attribute__((used)) void *p___fixtfsi = (void *) funA;
extern "C" void __fixtfsi() {
    SYMBOL_HOOK( p___fixtfsi);
}
extern "C" __attribute__((used)) void *p___fixtfti = (void *) funA;
extern "C" void __fixtfti() {
    SYMBOL_HOOK( p___fixtfti);
}
extern "C" __attribute__((used)) void *p___fixunsdfdi = (void *) funA;
extern "C" void __fixunsdfdi() {
    SYMBOL_HOOK( p___fixunsdfdi);
}
extern "C" __attribute__((used)) void *p___fixunsdfti = (void *) funA;
extern "C" void __fixunsdfti() {
    SYMBOL_HOOK( p___fixunsdfti);
}
extern "C" __attribute__((used)) void *p___fixunssfdi = (void *) funA;
extern "C" void __fixunssfdi() {
    SYMBOL_HOOK( p___fixunssfdi);
}
extern "C" __attribute__((used)) void *p___fixunssfti = (void *) funA;
extern "C" void __fixunssfti() {
    SYMBOL_HOOK( p___fixunssfti);
}
extern "C" __attribute__((used)) void *p___fixunstfdi = (void *) funA;
extern "C" void __fixunstfdi() {
    SYMBOL_HOOK( p___fixunstfdi);
}
extern "C" __attribute__((used)) void *p___fixunstfsi = (void *) funA;
extern "C" void __fixunstfsi() {
    SYMBOL_HOOK( p___fixunstfsi);
}
extern "C" __attribute__((used)) void *p___fixunstfti = (void *) funA;
extern "C" void __fixunstfti() {
    SYMBOL_HOOK( p___fixunstfti);
}
extern "C" __attribute__((used)) void *p___fixunsxfdi = (void *) funA;
extern "C" void __fixunsxfdi() {
    SYMBOL_HOOK( p___fixunsxfdi);
}
extern "C" __attribute__((used)) void *p___fixunsxfti = (void *) funA;
extern "C" void __fixunsxfti() {
    SYMBOL_HOOK( p___fixunsxfti);
}
extern "C" __attribute__((used)) void *p___fixxfti = (void *) funA;
extern "C" void __fixxfti() {
    SYMBOL_HOOK( p___fixxfti);
}
extern "C" __attribute__((used)) void *p___floatditf = (void *) funA;
extern "C" void __floatditf() {
    SYMBOL_HOOK( p___floatditf);
}
extern "C" __attribute__((used)) void *p___floatsitf = (void *) funA;
extern "C" void __floatsitf() {
    SYMBOL_HOOK( p___floatsitf);
}
extern "C" __attribute__((used)) void *p___floattidf = (void *) funA;
extern "C" void __floattidf() {
    SYMBOL_HOOK( p___floattidf);
}
extern "C" __attribute__((used)) void *p___floattisf = (void *) funA;
extern "C" void __floattisf() {
    SYMBOL_HOOK( p___floattisf);
}
extern "C" __attribute__((used)) void *p___floattitf = (void *) funA;
extern "C" void __floattitf() {
    SYMBOL_HOOK( p___floattitf);
}
extern "C" __attribute__((used)) void *p___floattixf = (void *) funA;
extern "C" void __floattixf() {
    SYMBOL_HOOK( p___floattixf);
}
extern "C" __attribute__((used)) void *p___floatunditf = (void *) funA;
extern "C" void __floatunditf() {
    SYMBOL_HOOK( p___floatunditf);
}
extern "C" __attribute__((used)) void *p___floatunsitf = (void *) funA;
extern "C" void __floatunsitf() {
    SYMBOL_HOOK( p___floatunsitf);
}
extern "C" __attribute__((used)) void *p___floatuntidf = (void *) funA;
extern "C" void __floatuntidf() {
    SYMBOL_HOOK( p___floatuntidf);
}
extern "C" __attribute__((used)) void *p___floatuntisf = (void *) funA;
extern "C" void __floatuntisf() {
    SYMBOL_HOOK( p___floatuntisf);
}
extern "C" __attribute__((used)) void *p___floatuntitf = (void *) funA;
extern "C" void __floatuntitf() {
    SYMBOL_HOOK( p___floatuntitf);
}
extern "C" __attribute__((used)) void *p___floatuntixf = (void *) funA;
extern "C" void __floatuntixf() {
    SYMBOL_HOOK( p___floatuntixf);
}
extern "C" __attribute__((used)) void *p___gcc_personality_v0 = (void *) funA;
extern "C" void __gcc_personality_v0() {
    SYMBOL_HOOK( p___gcc_personality_v0);
}
extern "C" __attribute__((used)) void *p___getf2 = (void *) funA;
extern "C" void __getf2() {
    SYMBOL_HOOK( p___getf2);
}
extern "C" __attribute__((used)) void *p___gttf2 = (void *) funA;
extern "C" void __gttf2() {
    SYMBOL_HOOK( p___gttf2);
}
extern "C" __attribute__((used)) void *p___letf2 = (void *) funA;
extern "C" void __letf2() {
    SYMBOL_HOOK( p___letf2);
}
extern "C" __attribute__((used)) void *p___lshrti3 = (void *) funA;
extern "C" void __lshrti3() {
    SYMBOL_HOOK( p___lshrti3);
}
extern "C" __attribute__((used)) void *p___lttf2 = (void *) funA;
extern "C" void __lttf2() {
    SYMBOL_HOOK( p___lttf2);
}
extern "C" __attribute__((used)) void *p___modti3 = (void *) funA;
extern "C" void __modti3() {
    SYMBOL_HOOK( p___modti3);
}
extern "C" __attribute__((used)) void *p___muldc3 = (void *) funA;
extern "C" void __muldc3() {
    SYMBOL_HOOK( p___muldc3);
}
extern "C" __attribute__((used)) void *p___mulsc3 = (void *) funA;
extern "C" void __mulsc3() {
    SYMBOL_HOOK( p___mulsc3);
}
extern "C" __attribute__((used)) void *p___multc3 = (void *) funA;
extern "C" void __multc3() {
    SYMBOL_HOOK( p___multc3);
}
extern "C" __attribute__((used)) void *p___multf3 = (void *) funA;
extern "C" void __multf3() {
    SYMBOL_HOOK( p___multf3);
}
extern "C" __attribute__((used)) void *p___multi3 = (void *) funA;
extern "C" void __multi3() {
    SYMBOL_HOOK( p___multi3);
}
extern "C" __attribute__((used)) void *p___mulvdi3 = (void *) funA;
extern "C" void __mulvdi3() {
    SYMBOL_HOOK( p___mulvdi3);
}
extern "C" __attribute__((used)) void *p___mulvsi3 = (void *) funA;
extern "C" void __mulvsi3() {
    SYMBOL_HOOK( p___mulvsi3);
}
extern "C" __attribute__((used)) void *p___mulvti3 = (void *) funA;
extern "C" void __mulvti3() {
    SYMBOL_HOOK( p___mulvti3);
}
extern "C" __attribute__((used)) void *p___mulxc3 = (void *) funA;
extern "C" void __mulxc3() {
    SYMBOL_HOOK( p___mulxc3);
}
extern "C" __attribute__((used)) void *p___negtf2 = (void *) funA;
extern "C" void __negtf2() {
    SYMBOL_HOOK( p___negtf2);
}
extern "C" __attribute__((used)) void *p___negti2 = (void *) funA;
extern "C" void __negti2() {
    SYMBOL_HOOK( p___negti2);
}
extern "C" __attribute__((used)) void *p___negvdi2 = (void *) funA;
extern "C" void __negvdi2() {
    SYMBOL_HOOK( p___negvdi2);
}
extern "C" __attribute__((used)) void *p___negvsi2 = (void *) funA;
extern "C" void __negvsi2() {
    SYMBOL_HOOK( p___negvsi2);
}
extern "C" __attribute__((used)) void *p___negvti2 = (void *) funA;
extern "C" void __negvti2() {
    SYMBOL_HOOK( p___negvti2);
}
extern "C" __attribute__((used)) void *p___netf2 = (void *) funA;
extern "C" void __netf2() {
    SYMBOL_HOOK( p___netf2);
}
extern "C" __attribute__((used)) void *p___paritydi2 = (void *) funA;
extern "C" void __paritydi2() {
    SYMBOL_HOOK( p___paritydi2);
}
extern "C" __attribute__((used)) void *p___parityti2 = (void *) funA;
extern "C" void __parityti2() {
    SYMBOL_HOOK( p___parityti2);
}
extern "C" __attribute__((used)) void *p___popcountdi2 = (void *) funA;
extern "C" void __popcountdi2() {
    SYMBOL_HOOK( p___popcountdi2);
}
extern "C" __attribute__((used)) void *p___popcountti2 = (void *) funA;
extern "C" void __popcountti2() {
    SYMBOL_HOOK( p___popcountti2);
}
extern "C" __attribute__((used)) void *p___powidf2 = (void *) funA;
extern "C" void __powidf2() {
    SYMBOL_HOOK( p___powidf2);
}
extern "C" __attribute__((used)) void *p___powisf2 = (void *) funA;
extern "C" void __powisf2() {
    SYMBOL_HOOK( p___powisf2);
}
extern "C" __attribute__((used)) void *p___powitf2 = (void *) funA;
extern "C" void __powitf2() {
    SYMBOL_HOOK( p___powitf2);
}
extern "C" __attribute__((used)) void *p___powixf2 = (void *) funA;
extern "C" void __powixf2() {
    SYMBOL_HOOK( p___powixf2);
}
extern "C" __attribute__((used)) void *p___register_frame = (void *) funA;
extern "C" void __register_frame() {
    SYMBOL_HOOK( p___register_frame);
}
extern "C" __attribute__((used)) void *p___register_frame_info = (void *) funA;
extern "C" void __register_frame_info() {
    SYMBOL_HOOK( p___register_frame_info);
}
extern "C" __attribute__((used)) void *p___register_frame_info_bases = (void *) funA;
extern "C" void __register_frame_info_bases() {
    SYMBOL_HOOK( p___register_frame_info_bases);
}
extern "C" __attribute__((used)) void *p___register_frame_info_table = (void *) funA;
extern "C" void __register_frame_info_table() {
    SYMBOL_HOOK( p___register_frame_info_table);
}
extern "C" __attribute__((used)) void *p___register_frame_info_table_bases = (void *) funA;
extern "C" void __register_frame_info_table_bases() {
    SYMBOL_HOOK( p___register_frame_info_table_bases);
}
extern "C" __attribute__((used)) void *p___register_frame_table = (void *) funA;
extern "C" void __register_frame_table() {
    SYMBOL_HOOK( p___register_frame_table);
}
extern "C" __attribute__((used)) void *p___subtf3 = (void *) funA;
extern "C" void __subtf3() {
    SYMBOL_HOOK( p___subtf3);
}
extern "C" __attribute__((used)) void *p___subvdi3 = (void *) funA;
extern "C" void __subvdi3() {
    SYMBOL_HOOK( p___subvdi3);
}
extern "C" __attribute__((used)) void *p___subvsi3 = (void *) funA;
extern "C" void __subvsi3() {
    SYMBOL_HOOK( p___subvsi3);
}
extern "C" __attribute__((used)) void *p___subvti3 = (void *) funA;
extern "C" void __subvti3() {
    SYMBOL_HOOK( p___subvti3);
}
extern "C" __attribute__((used)) void *p___trunctfdf2 = (void *) funA;
extern "C" void __trunctfdf2() {
    SYMBOL_HOOK( p___trunctfdf2);
}
extern "C" __attribute__((used)) void *p___trunctfsf2 = (void *) funA;
extern "C" void __trunctfsf2() {
    SYMBOL_HOOK( p___trunctfsf2);
}
extern "C" __attribute__((used)) void *p___trunctfxf2 = (void *) funA;
extern "C" void __trunctfxf2() {
    SYMBOL_HOOK( p___trunctfxf2);
}
extern "C" __attribute__((used)) void *p___ucmpti2 = (void *) funA;
extern "C" void __ucmpti2() {
    SYMBOL_HOOK( p___ucmpti2);
}
extern "C" __attribute__((used)) void *p___udivmodti4 = (void *) funA;
extern "C" void __udivmodti4() {
    SYMBOL_HOOK( p___udivmodti4);
}
extern "C" __attribute__((used)) void *p___udivti3 = (void *) funA;
extern "C" void __udivti3() {
    SYMBOL_HOOK( p___udivti3);
}
extern "C" __attribute__((used)) void *p___umodti3 = (void *) funA;
extern "C" void __umodti3() {
    SYMBOL_HOOK( p___umodti3);
}
extern "C" __attribute__((used)) void *p___unordtf2 = (void *) funA;
extern "C" void __unordtf2() {
    SYMBOL_HOOK( p___unordtf2);
}
void __attribute__  ((constructor (103))) hookInit() {
handle = dlopen("libgcc_s.so.1", RTLD_LAZY);
p__Unwind_Backtrace = dlsym(handle, "_Unwind_Backtrace");
p__Unwind_DeleteException = dlsym(handle, "_Unwind_DeleteException");
p__Unwind_FindEnclosingFunction = dlsym(handle, "_Unwind_FindEnclosingFunction");
p__Unwind_Find_FDE = dlsym(handle, "_Unwind_Find_FDE");
p__Unwind_ForcedUnwind = dlsym(handle, "_Unwind_ForcedUnwind");
p__Unwind_GetCFA = dlsym(handle, "_Unwind_GetCFA");
p__Unwind_GetDataRelBase = dlsym(handle, "_Unwind_GetDataRelBase");
p__Unwind_GetGR = dlsym(handle, "_Unwind_GetGR");
p__Unwind_GetIP = dlsym(handle, "_Unwind_GetIP");
p__Unwind_GetIPInfo = dlsym(handle, "_Unwind_GetIPInfo");
p__Unwind_GetLanguageSpecificData = dlsym(handle, "_Unwind_GetLanguageSpecificData");
p__Unwind_GetRegionStart = dlsym(handle, "_Unwind_GetRegionStart");
p__Unwind_GetTextRelBase = dlsym(handle, "_Unwind_GetTextRelBase");
p__Unwind_RaiseException = dlsym(handle, "_Unwind_RaiseException");
p__Unwind_Resume = dlsym(handle, "_Unwind_Resume");
p__Unwind_Resume_or_Rethrow = dlsym(handle, "_Unwind_Resume_or_Rethrow");
p__Unwind_SetGR = dlsym(handle, "_Unwind_SetGR");
p__Unwind_SetIP = dlsym(handle, "_Unwind_SetIP");
p___absvdi2 = dlsym(handle, "__absvdi2");
p___absvsi2 = dlsym(handle, "__absvsi2");
p___absvti2 = dlsym(handle, "__absvti2");
p___addtf3 = dlsym(handle, "__addtf3");
p___addvdi3 = dlsym(handle, "__addvdi3");
p___addvsi3 = dlsym(handle, "__addvsi3");
p___addvti3 = dlsym(handle, "__addvti3");
p___ashlti3 = dlsym(handle, "__ashlti3");
p___ashrti3 = dlsym(handle, "__ashrti3");
p___bswapdi2 = dlsym(handle, "__bswapdi2");
p___bswapsi2 = dlsym(handle, "__bswapsi2");
p___clear_cache = dlsym(handle, "__clear_cache");
p___clrsbdi2 = dlsym(handle, "__clrsbdi2");
p___clrsbti2 = dlsym(handle, "__clrsbti2");
p___clzdi2 = dlsym(handle, "__clzdi2");
p___clzti2 = dlsym(handle, "__clzti2");
p___cmpti2 = dlsym(handle, "__cmpti2");
p___cpu_indicator_init = dlsym(handle, "__cpu_indicator_init");
p___ctzdi2 = dlsym(handle, "__ctzdi2");
p___ctzti2 = dlsym(handle, "__ctzti2");
p___deregister_frame = dlsym(handle, "__deregister_frame");
p___deregister_frame_info = dlsym(handle, "__deregister_frame_info");
p___deregister_frame_info_bases = dlsym(handle, "__deregister_frame_info_bases");
p___divdc3 = dlsym(handle, "__divdc3");
p___divmodti4 = dlsym(handle, "__divmodti4");
p___divsc3 = dlsym(handle, "__divsc3");
p___divtc3 = dlsym(handle, "__divtc3");
p___divtf3 = dlsym(handle, "__divtf3");
p___divti3 = dlsym(handle, "__divti3");
p___divxc3 = dlsym(handle, "__divxc3");
p___emutls_get_address = dlsym(handle, "__emutls_get_address");
p___emutls_register_common = dlsym(handle, "__emutls_register_common");
p___enable_execute_stack = dlsym(handle, "__enable_execute_stack");
p___eqtf2 = dlsym(handle, "__eqtf2");
p___extenddftf2 = dlsym(handle, "__extenddftf2");
p___extendsftf2 = dlsym(handle, "__extendsftf2");
p___extendxftf2 = dlsym(handle, "__extendxftf2");
p___ffsdi2 = dlsym(handle, "__ffsdi2");
p___ffsti2 = dlsym(handle, "__ffsti2");
p___fixdfti = dlsym(handle, "__fixdfti");
p___fixsfti = dlsym(handle, "__fixsfti");
p___fixtfdi = dlsym(handle, "__fixtfdi");
p___fixtfsi = dlsym(handle, "__fixtfsi");
p___fixtfti = dlsym(handle, "__fixtfti");
p___fixunsdfdi = dlsym(handle, "__fixunsdfdi");
p___fixunsdfti = dlsym(handle, "__fixunsdfti");
p___fixunssfdi = dlsym(handle, "__fixunssfdi");
p___fixunssfti = dlsym(handle, "__fixunssfti");
p___fixunstfdi = dlsym(handle, "__fixunstfdi");
p___fixunstfsi = dlsym(handle, "__fixunstfsi");
p___fixunstfti = dlsym(handle, "__fixunstfti");
p___fixunsxfdi = dlsym(handle, "__fixunsxfdi");
p___fixunsxfti = dlsym(handle, "__fixunsxfti");
p___fixxfti = dlsym(handle, "__fixxfti");
p___floatditf = dlsym(handle, "__floatditf");
p___floatsitf = dlsym(handle, "__floatsitf");
p___floattidf = dlsym(handle, "__floattidf");
p___floattisf = dlsym(handle, "__floattisf");
p___floattitf = dlsym(handle, "__floattitf");
p___floattixf = dlsym(handle, "__floattixf");
p___floatunditf = dlsym(handle, "__floatunditf");
p___floatunsitf = dlsym(handle, "__floatunsitf");
p___floatuntidf = dlsym(handle, "__floatuntidf");
p___floatuntisf = dlsym(handle, "__floatuntisf");
p___floatuntitf = dlsym(handle, "__floatuntitf");
p___floatuntixf = dlsym(handle, "__floatuntixf");
p___gcc_personality_v0 = dlsym(handle, "__gcc_personality_v0");
p___getf2 = dlsym(handle, "__getf2");
p___gttf2 = dlsym(handle, "__gttf2");
p___letf2 = dlsym(handle, "__letf2");
p___lshrti3 = dlsym(handle, "__lshrti3");
p___lttf2 = dlsym(handle, "__lttf2");
p___modti3 = dlsym(handle, "__modti3");
p___muldc3 = dlsym(handle, "__muldc3");
p___mulsc3 = dlsym(handle, "__mulsc3");
p___multc3 = dlsym(handle, "__multc3");
p___multf3 = dlsym(handle, "__multf3");
p___multi3 = dlsym(handle, "__multi3");
p___mulvdi3 = dlsym(handle, "__mulvdi3");
p___mulvsi3 = dlsym(handle, "__mulvsi3");
p___mulvti3 = dlsym(handle, "__mulvti3");
p___mulxc3 = dlsym(handle, "__mulxc3");
p___negtf2 = dlsym(handle, "__negtf2");
p___negti2 = dlsym(handle, "__negti2");
p___negvdi2 = dlsym(handle, "__negvdi2");
p___negvsi2 = dlsym(handle, "__negvsi2");
p___negvti2 = dlsym(handle, "__negvti2");
p___netf2 = dlsym(handle, "__netf2");
p___paritydi2 = dlsym(handle, "__paritydi2");
p___parityti2 = dlsym(handle, "__parityti2");
p___popcountdi2 = dlsym(handle, "__popcountdi2");
p___popcountti2 = dlsym(handle, "__popcountti2");
p___powidf2 = dlsym(handle, "__powidf2");
p___powisf2 = dlsym(handle, "__powisf2");
p___powitf2 = dlsym(handle, "__powitf2");
p___powixf2 = dlsym(handle, "__powixf2");
p___register_frame = dlsym(handle, "__register_frame");
p___register_frame_info = dlsym(handle, "__register_frame_info");
p___register_frame_info_bases = dlsym(handle, "__register_frame_info_bases");
p___register_frame_info_table = dlsym(handle, "__register_frame_info_table");
p___register_frame_info_table_bases = dlsym(handle, "__register_frame_info_table_bases");
p___register_frame_table = dlsym(handle, "__register_frame_table");
p___subtf3 = dlsym(handle, "__subtf3");
p___subvdi3 = dlsym(handle, "__subvdi3");
p___subvsi3 = dlsym(handle, "__subvsi3");
p___subvti3 = dlsym(handle, "__subvti3");
p___trunctfdf2 = dlsym(handle, "__trunctfdf2");
p___trunctfsf2 = dlsym(handle, "__trunctfsf2");
p___trunctfxf2 = dlsym(handle, "__trunctfxf2");
p___ucmpti2 = dlsym(handle, "__ucmpti2");
p___udivmodti4 = dlsym(handle, "__udivmodti4");
p___udivti3 = dlsym(handle, "__udivti3");
p___umodti3 = dlsym(handle, "__umodti3");
p___unordtf2 = dlsym(handle, "__unordtf2");

}