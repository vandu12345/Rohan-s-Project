! NEWTON RAPHSON METHOD FOR ROOT FINDING OF THE SPIN GLASS PARAMETER

program root_finding
implicit none

real::avg_l,delta_l,sigma
real::x,root
integer::i,j

open(1, file = "spinglass.dat", action = "write")

delta_l = 0.0
avg_l = 0.0
x = 0.5


do i=1,100,1
do j=1,100,1


sigma = (avg_l-(delta_l**2/2.0))
call Raphson(x,sigma,avg_l,delta_l,root)

write(1,*) avg_l,delta_l,root,sigma

delta_l = delta_l+0.025

enddo

avg_l = avg_l+0.05
delta_l = 0.0

enddo
stop
end program

subroutine Raphson(x,coeff,a,b,root)

real::coeff,a,b,x
real::tol,h
real::y,deriv
integer::i

tol = 1.0e-6

do i = 1,25000

y = (log(x)-log(1-x)+log(10.0)+0.1962-(2*coeff*x))

deriv = ((1/x)+(1/1-x)-(2*coeff))

if (deriv == 0) then
    write(*,*) "Error: derivative is zero"
    return
endif 

h = y/deriv

if(abs(h).le.tol) then
go to 10
!write(1,*) "These are the roots for SG system"
!write(1,*) a,b,x,coeff
else
x = x-h
endif
10 enddo
return
end
