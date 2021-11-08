{
  description = "A C++ parser for a minimal XML-like dialect";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
    tinycmmc.url = "gitlab:grumbel/cmake-modules";
  };

  outputs = { self, nix, nixpkgs, flake-utils, tinycmmc }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in rec {
        packages = flake-utils.lib.flattenTree {
          babyxml = pkgs.stdenv.mkDerivation {
            pname = "babyxml";
            version = "0.0.0";
            src = nixpkgs.lib.cleanSource ./.;
            nativeBuildInputs = [ pkgs.cmake pkgs.ninja pkgs.gcc tinycmmc.defaultPackage.${system} ];
           };
        };
        defaultPackage = packages.babyxml;
      });
}
