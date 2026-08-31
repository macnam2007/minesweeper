{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  # nativeBuildInputs chứa các công cụ hỗ trợ quá trình build
  nativeBuildInputs = with pkgs; [
    pkg-config
  ];
  
  # buildInputs chứa các thư viện sẽ được liên kết (link) vào code
  buildInputs = with pkgs; [
    sfml
  ];
}