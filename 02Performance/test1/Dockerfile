FROM gcc:latest

WORKDIR /

COPY test1.cpp ./

RUN g++ -std=c++11 -o test1 test1.cpp -lssl -lcrypto

CMD ["/test1"]