all: xbuild run

xbuild:
	xcodebuild -project Crypt.xcodeproj

run:
	open build/Release/Crypt.app
