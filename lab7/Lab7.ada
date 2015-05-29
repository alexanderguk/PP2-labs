-----------------------------------
-- PP-2 Lab 7                    --
-- Lab 7: Ada. Rendezvous        --
-- Guk Alexander                 --
-- IP-22                         --
-- 28.05.2015                    --
-----------------------------------

with Ada.Text_IO, Ada.Integer_Text_IO;
use  Ada.Text_IO, Ada.Integer_Text_IO;

procedure lab7 is
	N: Integer:=8;
	p: Integer:=8;
	H: Integer:=N/p;
	Value : Integer:=1;

	type Vector is array (integer range<>) of integer;
	type Matrix is array (Integer range <>) of  Vector(1..N);
	subtype VectorH is Vector (1..H);
	subtype MatrixH is Matrix (1..H);
	subtype MatrixN is Matrix (1..n);
	subtype VectorN is Vector (1..n);
	
	procedure calculateAh(ME : in MatrixN; MK : in MatrixH; B : in VectorH; C : in VectorN; Alpha : in Integer; A : out VectorH) is
		Y : VectorN;
		e : Integer;
	begin
	    for i in 1..H loop
	        A(i):=0;
			for j in 1..N loop
	            Y(j):= 0;
	            for k in 1..N loop
	            	Y(j) := Y(j) + ME(j)(k) * MK(i)(k);
	            end loop;
	        end loop; 
			e := 0;
	        for k in 1..N loop
	        	e := e + Y(k) * C(k);	
	        end loop;
	        A(i) := alpha * B(i) + e;
	    end loop;
	end calculateAh;
	
	function transp_matr(M : in MatrixN) return MatrixN is
		ml : MatrixN;
	begin
		for i in 1..N loop
			for J in 1..N loop
				ml(J)(i):= M(i)(j);
			end loop;
		end loop;
		return ml;
	end transp_matr;

	procedure Input_Vector(V : out VectorN) is
	begin
		for i in 1..N loop
			V(i) := value;
		end loop;
	end Input_Vector;

	procedure Input_Matrix(M : out MatrixN) is
	begin
		for i in 1..N loop
			Input_Vector(M(i));
		end loop;
	end Input_Matrix;

	procedure Output_Vector(V : in VectorN) is
	begin
		for i in 1..N loop
			Put(V(i));
		end loop;
		New_Line;
	end Output_Vector;

	procedure Output_Matrix(M : in MatrixN) is
	begin
		for i in 1..N loop
			Output_Vector(M(i));
		end loop;
		New_Line;
	end Output_Matrix;

	procedure Output_Vector(V : in Vector; Size : in Integer) is
	begin
		for i in 1..Size loop
			Put(V(i));
		end loop;
		New_Line;
	end Output_Vector;

	procedure Output_Matrix(M : in Matrix; Size : in Integer) is
	begin
		for i in 1..Size loop
			Output_Vector(M(i));
		end loop;
		New_Line;
	end Output_Matrix;

	task T1 is 
		entry data_B_C_alpha(B : in Vector; C : in VectorN; alpha : in integer);
		entry Calculate_A(A : out Vector);
	end T1;
 	task T2 is 
 		entry data_mE_MK(ME : in MatrixN; MK : in Matrix);
		entry data_B_C_alpha(B : in Vector; C : in VectorN; alpha : in integer);
 		entry Calculate_A(A : out Vector);
 	end T2;
 	task T3 is 
 		entry data_mE_MK(ME : in MatrixN; MK : in Matrix);
		entry data_B_C_alpha(B : in Vector; C : in VectorN; alpha : in integer);
 		entry Calculate_A(A : out Vector);
 	end T3;
 	task T4 is 
 		entry data_mE_MK(ME : in MatrixN; MK : in Matrix);
		entry data_B_C_alpha(B : in Vector; C : in VectorN; alpha : in integer);
 		entry Calculate_A(A : out Vector);
 	end T4;
 	task T5 is 
 		entry data_mE_MK(ME : in MatrixN; MK : in Matrix);
		entry data_B_C_alpha(B : in Vector; C : in VectorN; alpha : in integer);
 		entry Calculate_A(A : out Vector);
 	end T5;
 	task T6 is 
 		entry data_mE_MK(ME : in MatrixN; MK : in Matrix);
		entry data_B_C_alpha(B : in Vector; C : in VectorN; alpha : in integer);
 		entry Calculate_A(A : out Vector);
 	end T6;
 	task T7 is 
 		entry data_mE_MK(ME : in MatrixN; MK : in Matrix);
		entry data_B_C_alpha(B : in Vector; C : in VectorN; alpha : in integer);
 		entry Calculate_A(A : out Vector);
 	end T7;
 	task T8 is 
 		entry data_mE_MK(ME : in MatrixN; MK : in Matrix);
 	end T8;
 ------------------------------------------------
 	task body T1 is
 		MK1 : MatrixN;
 		C1 : VectorN;
 		ME1 : MatrixN;
 		B1 : Vector(1..5*h);
 		alpha1 : Integer;
 		A1 : Vector(1..5*h);
 	begin
		New_Line;
 		Put("T1 started");
		Input_Matrix(ME1);
		Input_Matrix(MK1);

		T2.Data_ME_MK(ME1, MK1(H+1..5*h));
		T7.Data_ME_MK(ME1, MK1(5*H+1..8*h));

 		accept Data_B_C_alpha(B : in Vector; C : in VectorN; alpha : in integer) do
 			B1:= B;
 			C1:= C;
 			alpha1:= alpha;
 		end Data_B_C_alpha;
 		T2.Data_B_C_Alpha(B1(H+1..5*h), C1, alpha1);

 		calculateAh(ME1, MK1(1..H), B1(1..H), C1, alpha1, A1(1..H));
		T2.Calculate_A(A1(H+1..5*h));
 		accept Calculate_A(A : out Vector) do
 			A:= A1;
 		end Calculate_A;

		New_Line;
 		Put("T1 finished");
 	end T1;
 ------------------------------------------------
 	task body T2 is
 		MK2 : Matrix(H+1..5*h);
 		C2 : VectorN;
 		ME2 : MatrixN;
 		B2 : Vector(H+1..5*h);
 		alpha2 : Integer;
 		A2 : Vector(H+1..5*H);
 	begin
		New_Line;
 		Put("T2 started");
 		accept Data_ME_MK(ME : in MatrixN; MK : in Matrix) do
 			ME2:= ME;
 			MK2:= MK;
 		end Data_ME_MK;
 		T3.Data_ME_MK(ME2, MK2(2*h+1..3*h));
 		T4.Data_ME_MK(ME2, MK2(3*h+1..5*h));

 		accept Data_B_C_Alpha(B : in Vector; C : in VectorN; Alpha : in integer) do
 			b2 := b;
 			c2:= c;
			alpha2:=alpha;
 		end Data_B_C_Alpha;
		T3.Data_B_C_Alpha(B2(2*h+1..3*h), C2, Alpha2);
 		T4.Data_B_C_Alpha(B2(3*h+1..5*h), C2, Alpha2);

 		calculateAh(ME2, MK2(h+1..2*H), B2(h+1..2*H), C2, alpha2, A2(h+1..2*H));
 
 		T3.Calculate_A(A2(2*H+1..H*3));
 		T4.Calculate_A(A2(3*H+1..H*5));
 		accept Calculate_A(A : out Vector) do
 			A:= A2;
 		end Calculate_A;
		New_Line;
 		Put("T2 finished");
 	end T2;
 	------------------------------------------------
 	task body T3 is
 		MK3 : Matrix(2*h+1..3*H);
 		C3 : VectorN;
 		ME3 : MatrixN;
 		B3 : Vector(2*H+1..3*H);
 		alpha3 : Integer;
 		A3 : Vector(2*H+1..3*h);
 	begin
		New_Line;
 		Put("T3 started");
 		accept Data_ME_MK(ME : in MatrixN; MK : in Matrix) do
 			ME3:= ME;
 			MK3:= MK;
 		end Data_ME_MK;

 		accept Data_B_C_Alpha(B : in Vector; C : in VectorN; Alpha : in integer) do
 			b3 := b;
 			c3:= c;
			alpha3:=alpha;
 		end Data_B_C_Alpha;
 		
 		calculateAh(ME3, MK3, B3, C3, alpha3, A3(2*H+1..3*H));
 		accept Calculate_A(A : out Vector) do
 			A:= A3;
 		end Calculate_A;
		New_Line;
 		Put("T3 finished");
 	end T3;
 	------------------------------------------------
 	task body T4 is
 		MK4 : Matrix(3*h+1..5*h);
 		C4 : VectorN;
 		ME4 : MatrixN;
 		B4 : Vector(3*h+1..5*h);
 		alpha4 : Integer;
 		A4 : Vector(3*H+1..5*H);
 	begin
		New_Line;
 		Put("T4 started");
 		accept Data_ME_MK(ME : in MatrixN; MK : in Matrix) do
 			ME4:= ME;
 			MK4:= MK;
 		end Data_ME_MK;
 		T5.Data_ME_MK(ME4, MK4(4*h+1..5*h));

 		accept Data_B_C_Alpha(B : in Vector; C : in VectorN; Alpha : in integer) do
 			b4 := b;
 			c4:= c;
			alpha4:=alpha;
 		end Data_B_C_Alpha;
 		t5.Data_B_C_Alpha(B4(4*h+1..5*h), C4, Alpha4);

 		calculateAh(ME4, MK4(3*h+1..4*h), B4(3*h+1..4*h), C4, alpha4, A4(3*h+1..4*h));
 
 		T5.Calculate_A(a4(4*H+1..5*H));
 		accept Calculate_A(A : out Vector) do
 			A:= A4;
 		end Calculate_A;
		New_Line;
 		Put("T4 finished");
 	end T4;
 	------------------------------------------------
 	task body T5 is
 		MK5 : Matrix(4*H+1..5*H);
 		C5 : VectorN;
 		ME5 : MatrixN;
 		B5 : Vector(4*H+1..5*H);
 		alpha5 : Integer;
 		A5 : Vector(4*H+1..5*H);
 	begin
		New_Line;
 		Put("T5 started");
 		accept Data_ME_MK(ME : in MatrixN; MK : in Matrix) do
 			ME5:= ME;
 			MK5:= MK;
 		end Data_ME_MK;

 		accept Data_B_C_Alpha(B : in Vector; C : in VectorN; Alpha : in integer) do
 			b5 := b;
 			c5:= c;
			alpha5:=alpha;
 		end Data_B_C_Alpha;
 		
 		calculateAh(ME5, MK5, B5, C5, alpha5, A5(4*H+1..5*H));
 		accept Calculate_A(A : out Vector) do
 			A:= A5;
 		end Calculate_A;
		New_Line;
 		Put("T5 finished");
 	end T5;
 	------------------------------------------------
 	task body T6 is
 		MK6 : Matrix(5*H+1..6*H);
 		C6 : VectorN;
 		ME6 : MatrixN;
 		B6 : Vector(5*H+1..6*H);
 		alpha6 : Integer;
 		A6 : Vector(5*H+1..6*H);
 	begin
		New_Line;
 		Put("T6 started");
 		accept Data_ME_MK(ME : in MatrixN; MK : in Matrix) do
 			ME6:= ME;
 			MK6:= MK;
 		end Data_ME_MK;

 		accept Data_B_C_Alpha(B : in Vector; C : in VectorN; Alpha : in integer) do
 			b6 := b;
 			c6:= c;
			alpha6:=alpha;
 		end Data_B_C_Alpha;
 		
 		calculateAh(ME6, MK6, B6, C6, alpha6, A6(5*H+1..6*H));
 		accept Calculate_A(A : out Vector) do
 			A:= A6;
 		end Calculate_A;
		New_Line;
 		Put("T6 finished");
 	end T6;
 	------------------------------------------------
 	task body T7 is
 		MK7 : Matrix(5*H+1..8*H);
 		C7 : VectorN;
 		ME7 : MatrixN;
 		B7 : Vector(1..7*H);
 		alpha7 : Integer;
 		A7 : Vector(1..7*H);
 	begin
		New_Line;
 		Put("T7 started");
 		accept Data_ME_MK(ME : in MatrixN; MK : in Matrix) do
 			ME7:= ME;
 			MK7:= MK;
 		end Data_ME_MK;
 		T6.Data_ME_MK(ME7, MK7(5*h+1..6*h));
 		T8.Data_ME_MK(ME7, MK7(7*h+1..8*h));

 		accept Data_B_C_Alpha(B : in Vector; C : in VectorN; Alpha : in integer) do
 			b7 := b;
 			c7:= c;
			alpha7:=alpha;
 		end Data_B_C_Alpha;
 		t1.Data_B_C_Alpha(B7(1..5*h), C7, Alpha7);
 		t6.Data_B_C_Alpha(B7(5*h+1..6*h), C7, Alpha7);
 
 		calculateAh(ME7, MK7(H*6+1..h*7), B7(H*6+1..h*7), C7, alpha7, A7(H*6+1..h*7));
 		T6.Calculate_A(A7(5*H+1..6*H));
 		T1.Calculate_A(A7(1..5*H));
 		accept Calculate_A(A : out Vector) do
 			A:= A7;
 		end Calculate_A;
		New_Line;
 		Put("T7 finished");
 	end T7;
 	------------------------------------------------
 	task body T8 is
 		MK8 : Matrix(7*H+1..8*H);
 		C8 : VectorN;
 		ME8 : MatrixN;
 		B8 : VectorN;
 		Alpha8 : Integer;
 		A8 : VectorN;
 	begin
		New_Line;
 		Put("T8 started");
		Input_Vector(B8);
		Input_Vector(C8);
		alpha8 := 1;
 		
 		accept Data_ME_MK(ME : in MatrixN; MK : in Matrix) do
 			ME8:= ME;
 			MK8:= MK;
 		end Data_ME_MK;
 		t7.Data_B_C_Alpha(B8(1..7*h), C8, Alpha8);
 
 		calculateAh(ME8, MK8(H*7+1..H*8), B8(H*7+1..H*8), C8, alpha8, A8(H*7+1..H*8));
 		T7.Calculate_A(A8(1..7*H));
 	
 		Output_vector(A8);
		New_Line;
 		Put("T8 finished");
 	end T8;
 Begin	
       null;
 end lab7;

