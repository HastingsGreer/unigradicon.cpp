#include <torch/script.h>

#include <iostream>
#include <memory>

int main(int argc, const char* argv[]) {

    torch::jit::script::Module module;
    try {
	    module = torch::jit::load("traced_unigradicon.pt");
		   }
    catch ( const c10::Error& e) {
	    std::cerr << e.what() << std::endl;
	    std::cerr << "error loading unigradicon" << std::endl;
	    return -1;
    }
    std::cout << "unigradicon loaded" <<std::endl;
}
