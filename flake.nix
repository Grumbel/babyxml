{
  description = "A C++ parser for a minimal XML-like dialect";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?ref=nixos-24.05";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { self, nixpkgs, tinycmmc }:
    tinycmmc.lib.eachSystemWithPkgs (pkgs:
      {
        packages = rec {
          default = babyxml;

          babyxml = pkgs.stdenv.mkDerivation {
            pname = "babyxml";
            version = "0.0.0";

            src = ./.;

            cmakeFlags = [
              "-DBUILD_EXTRA=ON"
            ];

            nativeBuildInputs = with pkgs; [
              buildPackages.cmake
            ];

            buildInputs = [
              tinycmmc.packages.${pkgs.system}.default
            ];
           };
        };
      }
    );
}
