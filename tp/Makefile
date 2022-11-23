#
# Copyright 2021 Alysson Ribeiro da Silva - Federal University of Minas Gerais
#
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to deal 
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
# of the Software, and to permit persons to whom the Software is furnished to do 
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall
#CXXFLAGS = -std=c++11 -O3 -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
ASSETS_OUTPUT_FOLDER = ./assets/out/

# all sources, objs, and header files
MAIN = main
TARGET = quicksort
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

use:
#	$(BIN_FOLDER)$(TARGET) -v 1 -s 100 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida1.txt

#	$(BIN_FOLDER)$(TARGET) -v 2 -s 100 -k 3 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida2_3.txt
#	$(BIN_FOLDER)$(TARGET) -v 2 -s 100 -k 5 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida2_5.txt
#	$(BIN_FOLDER)$(TARGET) -v 2 -s 100 -k 7 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida2_7.txt	

	$(BIN_FOLDER)$(TARGET) -v 3 -s 100 -m 10 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida3_10.txt
	$(BIN_FOLDER)$(TARGET) -v 3 -s 100 -m 100 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida3_100.txt

	$(BIN_FOLDER)$(TARGET) -v 4 -s 100 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida4.txt

	$(BIN_FOLDER)$(TARGET) -v 5 -s 100 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida5.txt

	$(BIN_FOLDER)$(TARGET) -v 6 -s 100 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida6.txt

	$(BIN_FOLDER)$(TARGET) -v 7 -s 100 -i ./assets/entrada_padrao.txt -o $(BIN_FOLDER)saida7.txt

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)* $(ASSETS_OUTPUT_FOLDER)*
