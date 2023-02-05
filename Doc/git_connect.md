## 云服务器的git访问

- 本地可以通过梯子解决访问问题，云服务器可以通过设置/etc/hosts解决问题，测试有效
```
sudo vim /etc/hosts
 
# github
204.232.175.78 http://documentcloud.github.com
207.97.227.239 http://github.com
204.232.175.94 http://gist.github.com
107.21.116.220 http://help.github.com
207.97.227.252 http://nodeload.github.com
199.27.76.130 http://raw.github.com
107.22.3.110 http://status.github.com
204.232.175.78 http://training.github.com
207.97.227.243 http://www.github.com
```