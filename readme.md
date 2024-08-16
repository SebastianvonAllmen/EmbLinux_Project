might need to add the /build
``` bash
mkdir /build 
```


free port: (testing)
```
sudo lsof -t -i:8888 | xargs sudo kill && sudo lsof -t -i:8080 | xargs sudo kill
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
sudo apt-get install libi2c-dev i2c-tools
sudo apt-get install libmicrohttpd-dev
```

executing:
```
./EmbLinux_Project client 146.136.88.38
```

# Run
First start the server programm itself
then start the client programm

