# Maintainer: Developer <developer@arch.linux>
pkgname=minifetch
pkgver=1.0.0
pkgrel=1
pkgdesc="A fast C fetch tool with dynamic OS ASCII art"
arch=('x86_64')
license=('MIT')
depends=('glibc')

build() {
  # Compiling directly from the main directory
  gcc "$srcdir/../minifetch.c" -o minifetch
}

package() {
  install -Dm755 minifetch "$pkgdir/usr/bin/minifetch"
}
