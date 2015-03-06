-----------------------------------
-- PP-2 Lab 1                    --
-- Guk Alexander                 --
-- IP-22                         --
-- 19.02.2015                    --
-----------------------------------

with Ada.Text_IO, Ada.Integer_Text_IO, Ada.Synchronous_Task_Control;
use Ada.Text_IO, Ada.Integer_Text_IO, Ada.Synchronous_Task_Control;

-- A=sort(B)*MO+a*K*(ME*MT)
procedure Main is
	
	-- dimension of vectors and matrixes
	N : Integer := 4000;

	-- number of processors
	p : Integer := 2;

	H : Integer := N / p;

	-- define of user's types
	type vector is array (1..N) of integer;
	type matrix is array (1..N) of Vector;
	B, K, Result : Vector;
	MO, ME, MT : Matrix;
	a : Integer;

	S0, S1, S2, S3, S4 : Suspension_Object;

	-- vector autofill
	procedure Vector_Autofill(Number: in Integer; V: out Vector) is
	begin
		for i in 1..N loop
			V(I) := Number;
		end loop;
	end Vector_Autofill;

	-- matrix autifill
	procedure Matrix_Autofill(Number: in Integer; M: out Matrix) is
	begin
		for i in 1..N loop
			for J in 1..N loop
				M(I)(J) := Number;
			end loop;
		end loop;
	end Matrix_Autofill;

	-- vector output
	procedure Vector_Output(V: in Vector) is
	begin
		for i in 1..N loop
		    Ada.Integer_Text_IO.Put(V(i), Width => 0);
		    Ada.Text_IO.Put(" ");
		end loop;
		Ada.Text_IO.Put_Line("");
	end Vector_Output;

task Task_1 is
	
	pragma CPU(1);

end task_1;

task body task_1 is
	
	B1, K1 : vector;
	ME1 : Matrix;
	A1 : Integer;
	
	CurMin, Index, Temp : Integer;
	TempVector : Vector;
	TempMatrix : Matrix;
	TempVector2 : Vector;

begin
	
	put_Line("Task 1 has started");
	Put_Line("");
	-- Input
	Vector_Autofill(1, B);
	Vector_Autofill(1, K);
	Matrix_Autofill(1, MO);
	Matrix_Autofill(1, ME);
	Matrix_Autofill(1, MT);
	A := 1;

	-- Send signal0
	Set_True(S0);

	-- Sort subarray of B
	for i in 1..H loop
		for j in 1..H loop
			CurMin := B(J);
			Index := J;
			for K in J + 1..H loop
				if B(J + 1) < CurMin then
					CurMin := B(J + 1);
					Index := J + 1;
				end if;
			end loop;
			Temp := B(J);
			B(J) := B(Index);
			B(Index) := Temp;
		end loop;
	end loop;

	-- Waiting for signal1
	Suspend_Until_True(S1);

	-- Merge subarrays
	TempVector := B;
	for i in 1..H loop
		if TempVector(i) < TempVector(H + i) then
			B(I * 2 - 1) := TempVector(i);
			B(i * 2) := TempVector(H + I);
		else
			B(I * 2 - 1) := TempVector(H + i);
			B(i * 2) := TempVector(I);
		end if;
	end loop;
	-- Copying B
	B1 := B;

	-- Waiting for signal2
	Suspend_Until_True(S2);

	-- Send signal3
	Set_True(S3);

	-- Copying K, ME, a
	K1 := K;
	ME1 := ME;
	A1 := A;

	-- Calculating Result
	-- TempMatrix = ME1 * MT
	for i in 1..N loop
		for J in 1..H loop
			TempMatrix(i)(J) := 0;
			for k in 1..N loop
				TempMatrix(i)(j) := TempMatrix(I)(J) + ME1(i)(k)*MT(k)(J);
			end loop;
		end loop;
	end loop;
	-- TempVector = B1 * MO
	for i in 1..H loop
		TempVector(i) := 0;
		for j in 1..N loop
			TempVector(i) := TempVector(I) + B1(J) * MO(J)(I);
		end loop;
	end loop;
	-- TempVector2 = K1 * TempMatrix
	for i in 1..H loop
		TempVector2(i) := 0;
		for j in 1..N loop
			TempVector2(i) := TempVector2(I) + K1(J) * TempMatrix(J)(I);
		end loop;
	end loop;
	-- Result = TempVector + a1*TempVector2
	for i in 1..H loop
		Result(i) := TempVector(i) + A1 * TempVector2(i);
	end loop;

	-- Waiting for signal4
	Suspend_Until_True(S4);
	-- Output
	Put_Line("");
	Put_Line("Result:");
	Vector_Output(Result);
	put_Line("Task 1 has ended");
	
end task_1;
	
task Task_2 is
	
	pragma CPU(2);

end task_2;

task body task_2 is
	
	B2, K2 : vector;
	ME2 : Matrix;
	A2 : Integer;
	
	CurMin, Index, Temp : Integer;
	TempVector : Vector;
	TempMatrix : Matrix;
	TempVector2 : Vector;

begin
	
	put_Line("Task 2 has started");
	Put_Line("");

	-- Waiting for signal0
	Suspend_Until_True(S0);

	-- Sort subarray of B
	for i in H + 1..N loop
		for j in H + 1..N loop
			CurMin := B(J);
			Index := J;
			for K in J + 1..N loop
				if B(J + 1) < CurMin then
					CurMin := B(J + 1);
					Index := J + 1;
				end if;
			end loop;
			Temp := B(J);
			B(J) := B(Index);
			B(Index) := Temp;
		end loop;
	end loop;

	-- Send signal1
	Set_True(S1);

	-- Copying K, ME, a
	K2 := K;
	ME2 := ME;
	A2 := A;

	-- Send signal2
	Set_True(S2);

	-- Waiting for signal3
	Suspend_Until_True(S3);

	-- Copying B
	B2 := B;

	-- Calculating Result
	-- TempMatrix = ME1 * MT
	for i in 1..N loop
		for J in H + 1..N loop
			TempMatrix(i)(J) := 0;
			for k in 1..N loop
				TempMatrix(i)(j) := TempMatrix(I)(J) + ME2(i)(k)*MT(k)(J);
			end loop;
		end loop;
	end loop;
	-- TempVector = B1 * MO
	for i in H + 1..N loop
		TempVector(i) := 0;
		for j in 1..N loop
			TempVector(i) := TempVector(I) + B2(J) * MO(J)(I);
		end loop;
	end loop;
	-- TempVector2 = K1 * TempMatrix
	for i in H + 1..N loop
		TempVector2(i) := 0;
		for j in 1..N loop
			TempVector2(i) := TempVector2(I) + K2(J) * TempMatrix(J)(I);
		end loop;
	end loop;
	-- Result = TempVector + a1*TempVector2
	for i in H + 1..N loop
		Result(i) := TempVector(i) + A2 * TempVector2(i);
	end loop;

	-- Send signal4
	Set_True(S4);

	put_Line("Task 2 has ended");
	Put_Line("");
	
end task_2;

bEGIN

	NULL;

end Main;
