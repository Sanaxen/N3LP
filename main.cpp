#include "EncDec.hpp"

#include <iostream>
#include <random>

#ifdef USE_TEXT_COLOR

#include "util/text_color.hpp"
#endif

int main(int argc, char** argv){
  const std::string src = "./corpus/sample.en";
  const std::string tgt = "./corpus/sample.ja";
  const std::string srcDev = "./corpus/sample.en.dev";
  const std::string tgtDev = "./corpus/sample.ja.dev";

#ifdef USE_TEXT_COLOR

  console_create();
#endif

  FILE* fp_model = fopen("model/model.bin", "r");
  if (fp_model == NULL)
  {

	  FILE* fp = fopen((src + "_").c_str(), "r");
	  if (fp == NULL) return -1;
	  char* buf = new char[4096];
	  int linenum = 0;

	  std::vector<std::string> srcLine;
	  std::vector<std::string> tgtLine;
	  while (fgets(buf, 4096, fp) != NULL)
	  {
		  srcLine.push_back(buf);
		  linenum++;
	  }
	  fclose(fp);

	  fp = fopen((tgt + "_").c_str(), "r");
	  if (fp == NULL) return -1;
	  while (fgets(buf, 4096, fp) != NULL)
	  {
		  tgtLine.push_back(buf);
	  }
	  fclose(fp);

	  std::mt19937 mt;
	  std::uniform_real_distribution<> rand01(0.0, 1.0);

	  FILE* fp1 = fopen((srcDev + "_").c_str(), "w");
	  if (fp1 == NULL) return -1;
	  FILE* fp2 = fopen((tgtDev + "_").c_str(), "w");
	  if (fp2 == NULL) return -1;
	  FILE* fp3 = fopen((src + "_").c_str(), "w");
	  if (fp3 == NULL) return -1;
	  FILE* fp4 = fopen((tgt + "_").c_str(), "w");
	  if (fp4 == NULL) return -1;
	  for (int i = 0; i < srcLine.size(); i++)
	  {
		  if (rand01(mt) < 0.25)
		  {
			  fprintf(fp1, "%s", srcLine[i].c_str());
			  fprintf(fp2, "%s", tgtLine[i].c_str());
		  }
		  else
		  {
			  fprintf(fp3, "%s", srcLine[i].c_str());
			  fprintf(fp4, "%s", tgtLine[i].c_str());
		  }
	  }
	  fclose(fp1);
	  fclose(fp2);
	  fclose(fp3);
	  fclose(fp4);


  wakati("sample.ja_", "sample.ja");
  wakati("sample.en_", "sample.en");

  wakati("sample.ja.dev_", "sample.ja.dev");
  wakati("sample.en.dev_", "sample.en.dev");

  }
  if (fp_model )fclose(fp_model);

  Eigen::initParallel();
  EncDec::demo(src, tgt, srcDev, tgtDev);

  return 0;
}
