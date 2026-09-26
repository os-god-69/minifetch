# Maintainer: Developer <developer@arch.linux>
pkgname=minifetch
pkgver=1.0.4
pkgrel=1
pkgdesc="A fast C fetch tool with dynamic OS ASCII art"
arch=('x86_64')
license=('MIT')
depends=('glibc')

build() {
  # Fix: Compile directly from the active build directory dynamically
  cd "$srcdir/.."
  gcc minifetch.c -o minifetch
}

package() {
  cd "$srcdir/.."
  install -Dm755 minifetch "$pkgdir/usr/bin/minifetch"
}
