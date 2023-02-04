

### how 2 install glog
```
git clone https://github.com/google/glog.git
cd glog
cmake -S . -B build -G "Unix Makefiles"
# exit conda(conda deactivate): https://github.com/google/glog/issues/843
cd build 
make install # sudo make install
```

### how 2 use glog
```
#include <glog/logging.h>

int main()
{
    LOG(INFO) << "Hello,GLOG!";
}
```