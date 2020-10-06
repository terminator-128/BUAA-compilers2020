FROM gcc:10
WORKDIR /
COPY ./* ./
RUN gcc cxylex.cpp -lstdc++ -o program
RUN chmod +x program