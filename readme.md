might need to add the /build
``` bash
mkdir /build 
```


free port: (testing)
```
sudo lsof -t -i:8888 | xargs sudo kill
```

call port (testing)
``` 
nc 146.136.88.38 8888
```

device ip for mvp
```
146.136.88.38 - SvA
146.136.88.26 - RC
146.136.90.42 - Sva Host
```

needs:
``` bash
sudo apt install gpiod
sudo apt install libgpiod-dev
sudo apt-get install libmicrohttpd-dev
```

# Run
First start the server programm itself
then start the client programm

