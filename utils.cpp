#include "utils.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <tuple>

#include <getopt.h>

static void usage(void)
{
    printf(" USAGE: clang-faces <filename> [options]\n");
    exit(1);
}

std::vector<std::string>& split_args(std::string args)
{
    std::stringstream ss(args);
    std::istream_iterator<std::string> head(ss);
    std::istream_iterator<std::string> tail;
    // std::vector<std::string> vs(head, tail);
    // std::copy(vs.begin(), vs.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    return *(new std::vector<std::string>(head, tail));
}

std::tuple<std::string, std::string> parse_helper(int argc, char *argv[])
{
    int c, opt_idx;
    std::string filename, rest;

    // opterr = 0;
    struct option opts[] = {
        { "clang-opts", required_argument, NULL, 'c' },
        { "help", required_argument, NULL, 'h' },
        { NULL, 0, NULL, 0 }
    };
    while ((c = getopt_long(argc, argv, "", opts, &opt_idx)) != -1) {
        switch (c) {
            case 'c':
                rest = optarg;
                break;
            // case '?':
            //     std::cout << "unknown: " << optopt << "\n";
            //     vargs.push_back(std::string(optarg));
            //     break;
            case 'h':
            default:
                usage();
                break;
        }
    }

    if (optind >= argc) {
        std::cerr << "missing filename\n";
        exit(1);
    }

    filename = argv[optind];
    if (DEBUG) {
        ::printf("filename: %s\n", filename.c_str());
    }

    return std::tuple<std::string,std::string>(filename, rest);
}
