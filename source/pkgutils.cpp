#include "includes/package/pkgutils.hpp"

pkgutil::EtpPkgUtils::EtpPkgUtils()
{

}

pkgutil::EtpPkgUtils::~EtpPkgUtils()
{

}

void pkgutil::EtpPkgUtils::pkg_decompress(std::string package_path)
{
    bz2_decompress_package(package_path);

}


void pkgutil::EtpPkgUtils::bz2_decompress_package (std::string package_path)
{


    int flags;

    flags = ARCHIVE_EXTRACT_TIME;
    flags |= ARCHIVE_EXTRACT_PERM;
    flags |= ARCHIVE_EXTRACT_ACL;
    flags |= ARCHIVE_EXTRACT_FFLAGS;

    struct archive* package;
    struct archive* ext_package;
    struct archive_entry* entry;

    package = archive_read_new();

    archive_read_support_format_all(package);
    archive_read_support_compression_all(package);

    ext_package = archive_write_disk_new();
    archive_write_disk_set_options(ext_package, flags);
    archive_write_disk_set_standard_lookup(ext_package);

    int ret;

    if (( ret = archive_read_open_filename(package, package_path.c_str(), 10240)))
    {
        //raise Archive Except todo
        cout << "cannot open archive";
        return;
    }

    while (true)
    {

        ret = archive_read_next_header(package, &entry);
        if ( ret == ARCHIVE_EOF )
            break;
        if ( ret != ARCHIVE_OK)
        {   // warn
            cout << "!! " << archive_error_string(package);
        }

        if ( ret < ARCHIVE_WARN ){
            // raise except
            cout << " bad mojo";
            return;
        }
        ret = archive_write_header(ext_package, entry);
        if (ret != ARCHIVE_OK)
            cout << " !! " << archive_error_string(ext_package);
        else if (archive_entry_size(entry) > 0)
        {
            tar_copy_data(package, ext_package);
            if (ret != ARCHIVE_OK)
                cout << "!! " << archive_error_string(ext_package);
            if (ret < ARCHIVE_WARN){
                // raise exception
                cout << "bad mojo";
                return;
            }
        }

    }
    ret = archive_write_finish_entry(ext_package);
    if (ret != ARCHIVE_OK)
        cout << "!! " << archive_error_string(ext_package);
    if (ret < ARCHIVE_WARN)
    {
        // raise except
        cout << "lbad mojo";
        return;
    }
    archive_read_close(package);
    archive_read_free(package);
    archive_write_close(ext_package);
    archive_write_free(ext_package);

}


int pkgutil::EtpPkgUtils::tar_copy_data(struct archive* package_read, struct archive* package_write)
{

    size_t size;
    const void *buff;
    int ret;
#if ARCHIVE_VERSION >= 3000000
    int64_t offset;
#else
    off_t offset;
#endif

    while (true)
    {
        ret = archive_read_data_block(package_read, &buff, &size, &offset);
        if (ret == ARCHIVE_EOF)
            return(ARCHIVE_OK);
        if (ret != ARCHIVE_OK)
            return (ret);

        ret = archive_write_data_block(package_write, buff, size, offset);
        if (ret != ARCHIVE_OK)
        {
            return (ret);
        }
    }

}
