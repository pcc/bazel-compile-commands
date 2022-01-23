#include "bcc/options.hpp"

#include <boost/program_options.hpp>
#include <cstdlib>
#include <iostream>

namespace po = boost::program_options;

namespace bcc {
options
options::from_argv(int argc, char* argv[])
{

  // Declare the supported options.
  po::options_description desc(
    "Usage: bazle-compile-commands [-hvcC] TARGETS -- CONFIG");
  // clang-format off
  desc.add_options()
    ("help", "produce help message")
    ("verbose,v", "verbose, report more information")
    ("compiler,c", po::value<std::string>(), "use `compiler` as replacement for the bazel compiler wrapper script")
    ;
  // clang-format on

  // All remaining arguments are considerd as bazel target labels.
  po::positional_options_description targets;
  targets.add("targets", -1);

  po::variables_map vm;
  po::store(
    po::command_line_parser(argc, argv).options(desc).positional(targets).run(),
    vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cerr << desc << '\n';
    std::exit(0);
  }

  options result;
  result.verbose = vm.count("verbose") > 0;
  if (vm.count("compiler")) {
    result.compiler = vm["compiler"].as<std::string>();
  }

  if (vm.count("targets")) {
    result.targets = vm["targets"].as<std::vector<std::string>>();
  }
  return result;
}
} // namespace bcc
