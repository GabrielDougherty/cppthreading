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
            llvm_18
            clang_18
            cmake
            ninja
            pkg-config
            # Language servers for better VS Code integration
            clang-tools_18  # includes clangd
            cmake-language-server
          ];
          
          shellHook = ''
            export CC=clang
            export CXX=clang++
            export CMAKE_C_COMPILER=${pkgs.clang_18}/bin/clang
            export CMAKE_CXX_COMPILER=${pkgs.clang_18}/bin/clang++
            
            # Create VS Code settings if they don't exist
            mkdir -p .vscode
            cat > .vscode/settings.json << EOF
            {
                "C_Cpp.default.compilerPath": "${pkgs.clang_18}/bin/clang++",
                "C_Cpp.default.cppStandard": "c++23",
                "C_Cpp.default.intelliSenseMode": "clang-x64",
                "cmake.configureOnOpen": true,
                "cmake.generator": "Ninja",
                "clangd.path": "${pkgs.clang-tools_18}/bin/clangd"
            }
            EOF
            
            echo "C++ development environment loaded with LLVM 18"
            echo "VS Code settings updated automatically"
          '';
        };
      });
}