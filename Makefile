# Lazy build

build: 
	mingw32-g++ -std=c++17 -Wall \
	src/**.cpp headers/**.h \
	-ogen/ChuuDeeEnJin \
	-Iheaders \
	-Idependencies\SDL\include \
	-Idependencies\SDL_image\include \
	-Ldependencies\SDL\lib\x86 \
	-Ldependencies\SDL_image\lib\x86 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_image

run: 
	# gen/ChuuDeeEnJin

clean:
	rm gen/**