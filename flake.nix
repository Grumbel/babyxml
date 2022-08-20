{
  description = "A C++ parser for a minimal XML-like dialect";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, tinycmmc }:
    tinycmmc.lib.eachSystemWithPkgs (pkgs:
      {
        packages = rec {
          default = babyxml;

          babyxml = pkgs.stdenv.mkDerivation {
            pname = "babyxml";
            version = "0.0.0";

            src = nixpkgs.lib.cleanSource ./.;

            nativeBuildInputs = [
              pkgs.cmake
            ];

            buildInputs = [
              tinycmmc.packages.${pkgs.system}.default
            ];
           };
        };
      }
    );
}
