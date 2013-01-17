#include "includes/main.hpp"

namespace po = boost::program_options;

using std::string;

int main(int argc, char* argv[])
{

    po::options_description desc("etp available options");
    desc.add_options()
        ("help", "This message :)")
        ("install", po::value<string>(), "Install packages onto system;")
        ("remove", po::value<string>(), "Remove packages from system;")

    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    database::ETPSqlDatabase sql;

    sql.open();
    pkgutil::EtpPkgUtils epkg;

    epkg.pkg_decompress("includes.tbz");

    return 0;
}
