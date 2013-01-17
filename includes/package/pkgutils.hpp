#ifndef _H_ETP_PKGUTILS_INCLUDED__
#define _H_ETP_PKGUTILS_INCLUDED__

#include <iostream>

#include <stdio.h>

#include <archive.h>
#include <archive_entry.h>

namespace pkgutil
{

    using std::cout;

    class EtpPkgUtils
    {
        public:
            EtpPkgUtils();
            virtual ~EtpPkgUtils();

            void pkg_decompress(std::string package_path);

        private:
            void bz2_decompress_package(std::string package_path);
            int tar_copy_data(struct archive* package_read, struct archive* package_write);



    };
}

#endif
