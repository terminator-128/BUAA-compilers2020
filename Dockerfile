FROM ubuntu:16.04
RUN apt-get install gcc
WORKDIR /pascal_lex/
COPY ./* ./
RUN gcc cxylex.cpp -lstdc++ -o program
RUN chmod +x program