FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN g++ cxylex.cpp -o program
RUN chmod +x program