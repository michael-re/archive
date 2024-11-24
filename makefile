error:
	@echo ""
	@echo " please choose one of the following targets:"
	@echo "    - debug"
	@echo "    - release"
	@echo "    - clean"
	@echo ""
	@echo " eg: make debug"
	@echo ""
	@exit

release:
	cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
	cmake --build build

debug:
	cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
	cmake --build build

clean:
	cmake -E remove_directory build
	cmake -E remove_directory bin
