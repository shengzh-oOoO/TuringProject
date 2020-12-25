#Q = {start,mv1,readymv2,mv2,readyleft,left,readyright,right,reject,reject1,reject2,reject3,reject4,halt_reject,accept,accept1,accept2,accept3,halt_accept}
#S = {1,x,=}
#B = _
#G = {1,x,=,_,t,r,u,e,f,a,l,s}
#q0 = start
#F = {halt_accept,halt_reject}
#N = 3
;串需以1开头
start 1__ 1__ *** mv1
start x__ ___ r** reject
start =__ ___ r** reject
start ___ ___ *** reject

;将第一串1剪切到纸带2
mv1 1__ _1_ rr* mv1
mv1 x__ ___ rl* readymv2
mv1 =__ ___ r** reject
mv1 ___ ___ *** reject

;将第一串2剪切到纸带3
readymv2 11_ 11_ *** mv2
readymv2 =1_ ___ r** reject
readymv2 x1_ ___ r** reject
readymv2 _1_ ___ *** reject

mv2 11_ _11 r*r mv2
mv2 =1_ _1_ r*l readyleft
mv2 x1_ ___ r** reject
mv2 _1_ ___ *** reject
;开始循环比较,第二条纸带上的1用于计算循环次数，第三条纸带上的1用于表示每次循环删除的1的数量
;准备开始纸带3指针向左移动的循环，检查起始字符
readyleft 111 __1 rll left
readyleft _11 ___ *** reject
readyleft x11 ___ r** reject
readyleft =11 ___ r** reject
;对应删除纸带1上的1
left 111 _11 r*l left
left 1_1 __1 r*l left
left 11_ 11_ **r readyright
;准备开始纸带3指针向右移动的循环，检查起始字符
readyright 111 __1 rlr right
readyright _11 ___ *** reject
readyright x11 ___ r** reject
readyright =11 ___ r** reject
;对应删除纸带1上的1
right 111 _11 r*r right
right 1_1 __1 r*r right
right 11_ 11_ **l readyleft
;需要拒绝的各种情况
left 1__ ___ r** reject
right 1__ ___ r** reject

left _1_ ___ *** reject
right _1_ ___ *** reject

left __1 ___ *** reject
right __1 ___ *** reject

left _11 ___ *** reject
right _11 ___ *** reject

left x11 ___ r** reject
left =11 ___ r** reject
left x_1 ___ r** reject
left =_1 ___ r** reject
left x1_ ___ r** reject
left =1_ ___ r** reject
left x__ ___ r** reject
left =__ ___ r** reject
;接受
left ___ ___ *** accept
right ___ ___ *** accept
;打印true
accept ___ t__ r** accept1
accept1 ___ r__ r** accept2
accept2 ___ u__ r** accept3
accept3 ___ e__ r** halt_accept
;拒绝后需清空纸带1
reject 1__ ___ r** reject
reject x__ ___ r** reject
reject =__ ___ r** reject
reject 11_ ___ r** reject
reject x1_ ___ r** reject
reject =1_ ___ r** reject
reject 1_1 ___ r** reject
reject x_1 ___ r** reject
reject =_1 ___ r** reject
reject 111 ___ r** reject
reject x11 ___ r** reject
reject =11 ___ r** reject
;打印false
reject ___ f__ r** reject1
reject1 ___ a__ r** reject2
reject2 ___ l__ r** reject3
reject3 ___ s__ r** reject4
reject4 ___ e__ r** halt_reject
