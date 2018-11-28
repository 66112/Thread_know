lock:lock.cc
	g++ -o $@ $^ -lpthread -fpermissive -g
.PHONY:clean
clean:
	rm -f lock
