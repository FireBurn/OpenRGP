#include "openrgp/rgp_file.h"
#include <iostream>
#include <cstring>
using namespace openrgp;
int main(int argc, char** argv){
    // container test: load each file, verify magic + chunk walk consistency
    const char* files[] = {
      "/home/fireburn/AI/llama-deep/rgp/decode_94k/decode_94k_300nodes_submit0.rgp",
      "/home/fireburn/AI/llama-deep/rgp/decode_q8kv_32k_5tok.rgp",
    };
    int fails=0;
    for(auto f: files){
        Profile p; std::string err;
        if(!RgpFile::load(f,p,&err)){ std::cerr<<"FAIL load "<<f<<": "<<err<<"\n"; fails++; continue; }
        auto s=summarize(p);
        std::cout<<"OK "<<f<<"\n  gpu="<<s.gpu_name<<" se="<<s.num_se_traces
                 <<" codeobj="<<s.num_code_objects<<" pso="<<s.num_pso
                 <<" derived_spm="<<s.has_derived_spm<<"\n";
        // sanity: asic present, sqtt data pointers valid
        if(!p.asic){ std::cerr<<"  FAIL no asic\n"; fails++; }
        if(p.sqtt_data.size()!=p.sqtt_descs.size()){ std::cerr<<"  FAIL desc/data mismatch\n"; fails++; }
        for(auto* d: p.sqtt_data_ptr) if(!d){ std::cerr<<"  FAIL null sqtt ptr\n"; fails++; }
    }
    std::cout<<(fails? "FAILURES: ":"all passed: ")<<fails<<"\n";
    return fails?1:0;
}
