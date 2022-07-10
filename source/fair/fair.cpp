#include "fair.h"

#include <fstream>
#include <string_view>

namespace fair {
  auto run(int argc, char **argv) -> int {
    using std::string_view, std::ifstream, std::ofstream;
    using namespace std::literals;

    auto input_file  = string_view { "" };
    auto output_file = string_view { "" };

    for (int i = 0; i < argc; i++) {
      if ("-i"sv == argv[i] && i + 1 < argc)
        input_file = argv[++i];
      else if ("-o"sv == argv[i] && i + 1 < argc)
        output_file = argv[++i];
    }

    auto in  = ifstream { input_file.data() };
    auto out = ofstream { output_file.data() };

    if (!in)
      return 1;
    if (!out)
      return 1;

    char buf[1024] = { 0 };
    in.read(buf, sizeof(buf));

    if (string_view { buf }.find("main()") != string_view::npos) {
      out << "define i32 @main() {\n"
             "  ret i32 0\n"
             "}\n";
    }

    return 0;
  }
}

int fair_run(int argc, char **argv) {
  return fair::run(argc, argv);
}
