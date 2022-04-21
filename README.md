# DWM - Mahmoud Ashraf's fork of dwm!

## How I patch my fork
- branch out from `master` a new branch `patched`
```
git branch -b patched
```
- add this code into `/.git/config`
```
[remote "suckless"]
	url = https://git.suckless.org/dwm
	fetch = +refs/heads/*:refs/remotes/origin/*
```
so I can later keep my fork up-to-date with suckless source code by using
```sh
git pull suckless master
```
and then merge master into patched branch
- and here is the process to add new patch
```sh
git checkout -b ${patch_name}
curl -O ${patch_url}
patch -p1 < ${patch_file}
git commit -m "apply ${patch_name} patch"
git push -u origin HEAD
git checkout patched
git merge --squashed ${patch_name}
git commit
git push
```

## Patches
- [noborder](https://dwm.suckless.org/patches/noborder/)
- [pertag](https://dwm.suckless.org/patches/pertag/)
- [xresources](https://dwm.suckless.org/patches/xresources/)
- [fullgaps](https://dwm.suckless.org/patches/fullgaps/)
- [scratchpads](https://dwm.suckless.org/patches/scratchpads/)
- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/)
- [fullscreen](https://dwm.suckless.org/patches/fullscreen/)
- [losefullscreen](https://raw.githubusercontent.com/bakkeby/patches/master/dwm/dwm-losefullscreen-6.3.diff)
- [pango](https://dwm.suckless.org/patches/pango/)
- [ipc](https://dwm.suckless.org/patches/ipc/)
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [systray](https://dwm.suckless.org/patches/systray/)
- [stickyindicator](https://dwm.suckless.org/patches/stickyindicator/)
- [swallow](https://dwm.suckless.org/patches/swallow/)

## WIP
- [ ] integrate fullgaps with pertag
- [ ] reload xresources on run time and use ipc

## Bugs
- [ ] togglescratch crashes dwm when using it with ipc `dwm-msg`

