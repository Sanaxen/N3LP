#include "EncDec.hpp"

#include <iostream>

int main(int argc, char** argv){
  const std::string src = "./corpus/sample.en";
  const std::string tgt = "./corpus/sample.ja";
  const std::string srcDev = "./corpus/sample.en.dev";
  const std::string tgtDev = "./corpus/sample.ja.dev";

  wakati("sample.ja_", "sample.ja");
  wakati("sample.en_", "sample.en");

  wakati("sample.ja.dev_", "sample.ja.dev");
  wakati("sample.en.dev_", "sample.en.dev");

  Eigen::initParallel();
  EncDec::demo(src, tgt, srcDev, tgtDev);

  return 0;
}
