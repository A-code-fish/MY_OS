TOOLPATH = ../z_tools/
INCPATH  = ../z_tools/wm_OS/

MAKE     = $(TOOLPATH)make.exe -r
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
DEL      = del

default :
	$(MAKE) wm_OS.img

wm_OS.img : wm_OS/ipl10.bin wm_OS/wm_OS.sys Makefile\
        a/a.hrb hello3/hello3.hrb hello4/hello4.hrb hello5/hello5.hrb \
        winhelo/winhelo.hrb winhelo2/winhelo2.hrb winhelo3/winhelo3.hrb \
        star1/star1.hrb stars/stars.hrb stars2/stars2.hrb \
        lines/lines.hrb walk/walk.hrb noodle/noodle.hrb \
        beepdown/beepdown.hrb color/color.hrb color2/color2.hrb \
		sosu/sosu.hrb sosu2/sosu2.hrb sosu3/sosu3.hrb typeipl/typeipl.hrb \
		type/type.hrb bball/bball.hrb iroha/iroha.hrb invader/invader.hrb \
		calc/calc.hrb tview/tview.hrb
	$(EDIMG)   imgin:../z_tools/fdimg0at.tek \
        wbinimg src:wm_OS/ipl10.bin len:512 from:0 to:0 \
        copy from:wm_OS/wm_OS.sys to:@: \
        copy from:wm_OS/ipl10.nas to:@: \
        copy from:make.bat to:@: \
        copy from:a/a.hrb to:@: \
        copy from:hello3/hello3.hrb to:@: \
        copy from:hello4/hello4.hrb to:@: \
        copy from:hello5/hello5.hrb to:@: \
        copy from:winhelo/winhelo.hrb to:@: \
        copy from:winhelo2/winhelo2.hrb to:@: \
        copy from:winhelo3/winhelo3.hrb to:@: \
        copy from:star1/star1.hrb to:@: \
        copy from:stars/stars.hrb to:@: \
        copy from:stars2/stars2.hrb to:@: \
        copy from:lines/lines.hrb to:@: \
        copy from:walk/walk.hrb to:@: \
        copy from:noodle/noodle.hrb to:@: \
        copy from:beepdown/beepdown.hrb to:@: \
        copy from:color/color.hrb to:@: \
        copy from:color2/color2.hrb to:@: \
		copy from:sosu/sosu.hrb to:@: \
		copy from:sosu2/sosu2.hrb to:@: \
		copy from:sosu3/sosu3.hrb to:@: \
		copy from:typeipl/typeipl.hrb to:@: \
		copy from:type/type.hrb to:@: \
		copy from:bball/bball.hrb to:@: \
		copy from:iroha/iroha.hrb to:@: \
		copy from:nihongo/chinese.fnt to:@: \
		copy from:invader/invader.hrb to:@: \
		copy from:calc/calc.hrb to:@: \
		copy from:tview/tview.hrb to:@: \
        imgout:wm_OS.img

run :
	$(MAKE) wm_OS.img
	$(COPY) wm_OS.img ..\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../z_tools/qemu

install :
	$(MAKE) wm_OS.img
	$(IMGTOL) w a: wm_OS.img

full :
	$(MAKE) -C wm_OS
	$(MAKE) -C apilib
	$(MAKE) -C a
	$(MAKE) -C hello3
	$(MAKE) -C hello4
	$(MAKE) -C hello5
	$(MAKE) -C winhelo
	$(MAKE) -C winhelo2
	$(MAKE) -C winhelo3
	$(MAKE) -C star1
	$(MAKE) -C stars
	$(MAKE) -C stars2
	$(MAKE) -C lines
	$(MAKE) -C walk
	$(MAKE) -C noodle
	$(MAKE) -C beepdown
	$(MAKE) -C color
	$(MAKE) -C color2
	$(MAKE) -C sosu
	$(MAKE) -C sosu2
	$(MAKE) -C sosu3
	$(MAKE) -C typeipl
	$(MAKE) -C type
	$(MAKE) -C bball
	$(MAKE) -C iroha
	$(MAKE) -C invader
	$(MAKE) -C calc
	$(MAKE) -C tview
	$(MAKE) wm_OS.img

run_full :
	$(MAKE) full
	$(COPY) wm_OS.img ../z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../z_tools/qemu

install_full :
	$(MAKE) full
	$(IMGTOL) w a: wm_OS.img

run_os :
	$(MAKE) -C wm_OS
	$(MAKE) run

clean :


src_only :
	$(MAKE) clean
	-$(DEL) wm_OS.img

clean_full :
	$(MAKE) -C wm_OS     	clean
	$(MAKE) -C apilib       clean
	$(MAKE) -C a            clean
	$(MAKE) -C hello3       clean
	$(MAKE) -C hello4       clean
	$(MAKE) -C hello5       clean
	$(MAKE) -C winhelo      clean
	$(MAKE) -C winhelo2     clean
	$(MAKE) -C winhelo3     clean
	$(MAKE) -C star1        clean
	$(MAKE) -C stars        clean
	$(MAKE) -C stars2       clean
	$(MAKE) -C lines        clean
	$(MAKE) -C walk         clean
	$(MAKE) -C noodle       clean
	$(MAKE) -C beepdown     clean
	$(MAKE) -C color        clean
	$(MAKE) -C color2       clean
	$(MAKE) -C sosu       	clean
	$(MAKE) -C sosu2       	clean
	$(MAKE) -C sosu3       	clean
	$(MAKE) -C typeipl      clean
	$(MAKE) -C type         clean
	$(MAKE) -C bball        clean
	$(MAKE) -C iroha        clean
	$(MAKE) -C invader      clean
	$(MAKE) -C calc         clean
	$(MAKE) -C tview       	clean

src_only_full :
	$(MAKE) -C wm_OS     	src_only
	$(MAKE) -C apilib       src_only
	$(MAKE) -C a            src_only
	$(MAKE) -C hello3       src_only
	$(MAKE) -C hello4       src_only
	$(MAKE) -C hello5       src_only
	$(MAKE) -C winhelo      src_only
	$(MAKE) -C winhelo2     src_only
	$(MAKE) -C winhelo3     src_only
	$(MAKE) -C star1        src_only
	$(MAKE) -C stars        src_only
	$(MAKE) -C stars2       src_only
	$(MAKE) -C lines        src_only
	$(MAKE) -C walk         src_only
	$(MAKE) -C noodle       src_only
	$(MAKE) -C beepdown     src_only
	$(MAKE) -C color        src_only
	$(MAKE) -C color2       src_only
	$(MAKE) -C sosu       	src_only
	$(MAKE) -C sosu2       	src_only
	$(MAKE) -C sosu3       	src_only
	$(MAKE) -C typeipl      src_only
	$(MAKE) -C type      	src_only
	$(MAKE) -C bball     	src_only
	$(MAKE) -C iroha     	src_only
	$(MAKE) -C invader     	src_only
	$(MAKE) -C calc     	src_only
	$(MAKE) -C calc     	src_only
	$(MAKE) -C tview     	src_only
	-$(DEL) wm_OS.img

refresh :
	$(MAKE) full
	$(MAKE) clean_full
	-$(DEL) wm_OS.img
