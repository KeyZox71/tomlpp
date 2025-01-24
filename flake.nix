{
	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
		pogit = {
			url = "github:y-syo/pogit";
			inputs.nixpkgs.follows = "nixpkgs";
		};
	};

	outputs = inputs@{ nixpkgs, ... }: 
		let 
			supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
			forEachSupportedSystem = f: nixpkgs.lib.genAttrs supportedSystems (system: f {
				pkgs = import nixpkgs { inherit system; };
			});
		in {
			devShells = forEachSupportedSystem ({ pkgs }: {
				default = pkgs.mkShell.override
				{}
				{
					buildInputs = with pkgs;[

					];
					hardeningDisable = [ "all" ];
					packages = with pkgs; [
						gcc11
						clang_12
						norminette
						valgrind
						git
						gdb
						inputs.pogit.packages.${pkgs.system}.default
						python312Packages.compiledb
					];
				};
			});
		};
}

