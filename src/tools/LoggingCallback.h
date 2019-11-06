//
// Created by Sascha Roth on 05.11.19.
//

#pragma once
#include <stdarg.h>
#include <iostream>
#include <vector>
#include <stddef.h>
#include <string>

namespace ChickenHook {


        /*
         * Calculate number of characters that is required to apply pargs to format string.
         *
         * \return The number of characters that would be required by any printf function to format the string, not counting
         * 		the terminating null character. If an encoding error occurs, a negative number is returned.
         */
        int _vscprintf(const char *format, va_list pargs);

        /*
         * convert CFormatString and parameters into formatted std::string.
         */
        int vaListToString(const char *CFormatString, va_list argptr, std::string &result);

        /**
         * Use this to log into the provided logging callback
         */
        void log(const char *CFormatString, ...);

        /*
        * Set the logging callback
        */
        void setLogFunction(void (*logCallback)(const std::string &));

}