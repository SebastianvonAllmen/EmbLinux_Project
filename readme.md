Use this repo to copy files to raspy

might need to add the /build folder manually


free port:
```
sudo lsof -t -i:8888 | xargs sudo kill
```

call port
``` 
nc 146.136.88.38 8888
```

device ip for mvp
````
146.136.88.38 - SvA
146.136.88.26 - RC
146.136.90.42 - Sva Host
```

needs:
```
sudo apt install gpiod
sudo apt install libgpiod-dev
sudo apt-get install libi2c-dev i2c-tools
```

executing:
```
./EmbLinux_Project client 146.136.88.38
```

