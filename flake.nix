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
          # C toolchain
          clang
          clang-tools
          lldb

          # Build tools
          gnumake
          pkg-config

          # C library
          glibc.dev

          # Raylib
          raylib

          # Graphics / Wayland
          wayland
          wayland-protocols
          wayland-scanner
          wayland-utils
          libxkbcommon
          libffi
          mesa
          libGL
          libglvnd

          # Compilation database
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
