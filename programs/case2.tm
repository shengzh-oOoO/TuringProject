#Q = {start,mv1,readymv2,mv2,readyleft,left,readyright,right,reject,reject1,reject2,reject3,reject4,halt_reject,accept,accept1,accept2,accept3,halt_accept}
#S = {1,x,=}
#B = _
#G = {1,x,=,_,t,r,u,e,f,a,l,s}
#q0 = start
#F = {halt_accept,halt_reject}
#N = 3

start 1__ 1__ *** mv1
start x__ ___ r** reject
start =__ ___ r** reject
start ___ ___ *** reject

mv1 1__ _1_ rr* mv1
mv1 x__ ___ rl* readymv2
mv1 =__ ___ r** reject
mv1 ___ ___ *** reject

readymv2 11_ 11_ *** mv2
readymv2 =1_ ___ r** reject
readymv2 x1_ ___ r** reject
readymv2 _1_ ___ *** reject

mv2 11_ _11 r*r mv2
mv2 =1_ _1_ r*l readyleft
mv2 x1_ ___ r** reject
mv2 _1_ ___ *** reject

readyleft _11 ___ *** reject

readyleft 111 __1 rll left
left 111 _11 r*l left
left 1_1 __1 r*l left
left 11_ 11_ **r readyright
readyright 111 __1 rlr right
right 111 _11 r*r right
right 1_1 __1 r*r right
right 11_ 11_ **l readyleft

left 1__ ___ r** reject
right 1__ ___ r** reject

left _1_ ___ *** reject
right _1_ ___ *** reject
left __1 ___ *** reject
right __1 ___ *** reject
left _11 ___ *** reject
right _11 ___ *** reject

left ___ ___ *** accept
right ___ ___ *** accept

accept ___ t__ r** accept1
accept1 ___ r__ r** accept2
accept2 ___ u__ r** accept3
accept3 ___ e__ r** halt_accept

reject 1__ ___ r** reject
reject x__ ___ r** reject
reject =__ ___ r** reject

reject ___ f__ r** reject1
reject1 ___ a__ r** reject2
reject2 ___ l__ r** reject3
reject3 ___ s__ r** reject4
reject4 ___ e__ r** halt_reject
