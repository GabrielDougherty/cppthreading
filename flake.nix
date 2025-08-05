{
  description = "C++ Threading Project";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc14
            cmake
            ninja
            pkg-config
            # Language servers for better VS Code integration
            clang-tools  # includes clangd, works well with gcc too
            cmake-language-server
          ];
          
          shellHook = ''
            export CC=gcc
            export CXX=g++
            export CMAKE_C_COMPILER=${pkgs.gcc14}/bin/gcc
            export CMAKE_CXX_COMPILER=${pkgs.gcc14}/bin/g++
            
            # Create VS Code settings if they don't exist
            mkdir -p .vscode
            cat > .vscode/settings.json << EOF
            {
                "C_Cpp.default.compilerPath": "${pkgs.gcc14}/bin/g++",
                "C_Cpp.default.cppStandard": "c++23",
                "C_Cpp.default.intelliSenseMode": "gcc-x64",
                "cmake.configureOnOpen": true,
                "cmake.generator": "Ninja",
                "clangd.path": "${pkgs.clang-tools}/bin/clangd"
            }
            EOF
            
            echo "C++ development environment loaded with GCC 14"
            echo "VS Code settings updated automatically"
          '';
        };
      });
}