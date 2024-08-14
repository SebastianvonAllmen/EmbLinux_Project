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
```

needs:
```
sudo apt install gpiod
sudo apt install libgpiod-dev
```



