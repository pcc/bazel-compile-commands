#pragma once

#include <optional>
#include <string>
#include <vector>

namespace bcc {
struct options
{
  static options from_argv(int argc, char* argv[]);

  /// Be verbose.
  bool verbose{ false };
  /// Replace Bazel compiler with `cc`.
  std::optional<std::string> compiler{};
  /// Targets to consider for the generation of the `compile_commands.json`
  /// file.
  std::vector<std::string> targets{ "//..." };
  /// Flags to be forwarded to the `bazel query` call.
  std::vector<std::string> bazel_flags{};
};
} // namespace bcc
