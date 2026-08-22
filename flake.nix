{
  description = "C + Raylib development environment";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?ref=nixos-unstable";
  };
  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          clang
          clang-tools
          lldb
          gnumake
          pkg-config
          glibc.dev
          raylib
          wayland
          wayland-protocols
          wayland-scanner
          wayland-utils
          libxkbcommon
          libffi
          mesa
          libGL
          libglvnd
          bear
        ];
        env = {
          LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
            pkgs.raylib
            pkgs.wayland
            pkgs.libxkbcommon
            pkgs.libffi
            pkgs.mesa
            pkgs.libGL
            pkgs.libglvnd
          ];
        };
      };
    };
}
