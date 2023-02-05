### how 2 install armadillo

- download page : https://arma.sourceforge.net/download.html
- 参考：http://zhaoxuhui.top/blog/2020/10/11/armadillo-introduction-and-installation.html#1依赖库安装
- 上面装了还不够，还需要装hdf5，且版本最好是1.8（对于当前arma）：
    - 1.https://www.cnblogs.com/zhml/p/15102214.html
    - 2.https://blog.csdn.net/weixin_43819313/article/details/125861906
```
wget http://sourceforge.net/projects/arma/files/armadillo-11.4.3.tar.xz
apt-get install libopenblas-dev liblapack-dev libarpack2-dev libsuperlu-dev
tar -xf armadillo-11.4.3.tar.xz && cd armadillo-11.4.3
mkdir build && cd build && cmake ..
make -j8
make install
```

