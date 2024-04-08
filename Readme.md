To set up


```
cd ..

export PATH=$PATH:/usr/local/cuda-12.2/bin



git clone https://github.com/InsightSoftwareConsortium/ITK
mkdir ITK_build
cd ITK_build 
cmake ../ITK
make -j20
cd ..
cd unigradicon_lightning
pip install unigradicon
python make_torchscript_unigradicon.py

cd ..

wget https://download.pytorch.org/libtorch/cu121/libtorch-cxx11-abi-shared-with-deps-2.2.2%2Bcu121.zip
unzip libtorch-cxx11-abi-shared-with-deps-2.2.2+cu121.zip

mkdir unigradicon_lightning_build
cp unigradicon_lightning/traced_unigradicon.pt unigradicon_lightning_build
cd unigradicon_lightning_build

cmake ../unigradicon_lightning -DITK_DIR=../ITK_build -DTORCH_DIR=../libtorch/share/cmake/Torch
make
```



