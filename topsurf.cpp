#include "rice/Struct.hpp"
#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Enum.hpp"
#include <topsurf/api.h>
#include <topsurf/descriptor.h>

using namespace Rice;

// enum TOPSURF_SIMILARITY
TOPSURF_SIMILARITY topsurf_similarity(String similarity)
{
  if(similarity.str().compare("TOPSURF_COSINE") == 0)
    return TOPSURF_COSINE;
  else
    return TOPSURF_ABSOLUTE;
}

// bool DLLAPI TopSurf_Initialize(int imagedim, int top);
bool topsurf_initialize(int imagedim, int top)
{
  return TopSurf_Initialize(imagedim, top);
}

// void DLLAPI TopSurf_Terminate();
void topsurf_terminate()
{
  TopSurf_Terminate();
}

// bool DLLAPI TopSurf_LoadDictionary(const char *dictionarydir);
bool topsurf_loaddictionary(const char *dictionarydir)
{
  return TopSurf_LoadDictionary(dictionarydir);
}

// bool DLLAPI TopSurf_SaveDictionary(const char *dictionarydir);
bool topsurf_savedictionary(const char *dictionarydir)
{
  return TopSurf_SaveDictionary(dictionarydir);
}

// bool DLLAPI TopSurf_CreateDictionary(const char *imagedir, int clusters, int knn, int iterations, int points);
bool topsurf_createdictionary(const char *imagedir, int clusters, int knn, int iterations, int points)
{
  return TopSurf_CreateDictionary(imagedir, clusters, knn, iterations, points);
}

// bool DLLAPI TopSurf_ExtractDescriptor(const char *fname, TOPSURF_DESCRIPTOR &td);
Rice::Hash topsurf_extractdescriptor(const char *fname)
{
  TOPSURF_DESCRIPTOR td;
  TopSurf_ExtractDescriptor(fname, td);
  return td.to_h();
}

// bool DLLAPI TopSurf_SaveDescriptor(const char *fname, const TOPSURF_DESCRIPTOR &td);
bool topsurf_savedescriptor(String fname, String dname)
{
  TOPSURF_DESCRIPTOR td;
  return TopSurf_ExtractDescriptor(fname.c_str(), td) && TopSurf_SaveDescriptor(dname.c_str(), td);
}

// float DLLAPI TopSurf_CompareDescriptors(const TOPSURF_DESCRIPTOR &td1, const TOPSURF_DESCRIPTOR &td2, TOPSURF_SIMILARITY similarity);
float topsurf_comparedescriptors(String dname1, String dname2, String similarity_rb)
{
  TOPSURF_DESCRIPTOR td1, td2;
  TopSurf_LoadDescriptor(dname1.c_str(), td1);
  TopSurf_LoadDescriptor(dname2.c_str(), td2);

  return TopSurf_CompareDescriptors(td1, td2, topsurf_similarity(similarity_rb));
}

// float DLLAPI TopSurf_CompareDescriptors(const TOPSURF_DESCRIPTOR &td1, const TOPSURF_DESCRIPTOR &td2, TOPSURF_SIMILARITY similarity);
// float topsurf_comparedescriptors(const Rice::Hash td1_rb, const Rice::Hash td2_rb, String similarity_rb)
// {
//  TOPSURF_DESCRIPTOR td1(td1_rb), td2(td2_rb);
//  return TopSurf_CompareDescriptors(td1, td2, topsurf_similarity(similarity_rb));
// }

float topsurf_compareimages(String image1, String image2, String similarity_rb)
{
  TOPSURF_DESCRIPTOR td1, td2;
  TopSurf_ExtractDescriptor(image1.c_str(), td1);
  TopSurf_ExtractDescriptor(image2.c_str(), td2);

  return TopSurf_CompareDescriptors(td1, td2, topsurf_similarity(similarity_rb));
}

extern "C"

void Init_topsurf()
{

  Class rb_cTopsurf = define_class("Topsurf")
    .define_method("Initialize", &topsurf_initialize)
    .define_method("Terminate", &topsurf_terminate)
    .define_method("LoadDictionary", &topsurf_loaddictionary)
    .define_method("SaveDictionary", &topsurf_savedictionary)
    .define_method("CreateDictionary", &topsurf_createdictionary)
    .define_method("ExtractDescriptor", &topsurf_extractdescriptor)
    .define_method("SaveDescriptor", &topsurf_savedescriptor)
    .define_method("CompareDescriptors", &topsurf_comparedescriptors)
    .define_method("CompareImages", &topsurf_compareimages)
    ;
}
