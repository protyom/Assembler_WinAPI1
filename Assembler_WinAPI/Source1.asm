.686
PUBLIC AllDoubPalindroms
PUBLIC AllDoubPalindroms1
PUBLIC @AllDoubPalindroms2@8
.model flat
.data
	temp dd ?
	res db ?
	flag db 0
.code

AllDoubPalindroms proc stdcall, a: dword, n:dword
	push ecx
	push ebx
	push edx
	mov flag,0
	mov ecx,n
	xor eax,eax
	jecxz end_
	mov ebx,a
for_ :
	mov edx, [ebx]
	mov temp, edx
	push ebx
	call DoublePal
	pop ebx
	cmp res, 2
	jne continue_
	cmp flag, 0
	jne compare_
	mov eax,ebx
	mov flag, 1
	jmp continue_
compare_ :
	mov edx, [ebx]
	cmp [eax], edx
	jnl continue_
	mov eax,ebx
continue_ :
	add ebx, 4
	loop for_
end_:
	pop ebx
	xor edx,edx
	sub eax,a
	shr eax,2
	pop edx
	pop ecx
	cmp flag,0
	jne exit_
	mov eax,n
	inc eax
exit_:
	ret
AllDoubPalindroms endp

AllDoubPalindroms1 proc c, a: dword, n:dword
	push ecx
	push ebx
	push edx
	mov ecx,n
	mov flag,0
	xor eax,eax
	jecxz end_
	mov ebx,a
for_ :
	mov edx, [ebx]
	mov temp, edx
	push ebx
	call DoublePal
	pop ebx
	cmp res, 2
	jne continue_
	cmp flag, 0
	jne compare_
	mov eax,ebx
	mov flag, 1
	jmp continue_
compare_ :
	mov edx, [ebx]
	cmp [eax], edx
	jnl continue_
	mov eax,ebx
continue_ :
	add ebx, 4
	loop for_
end_:
	pop ebx
	xor edx,edx
	sub eax,a
	shr eax,2
	pop edx
	pop ecx
	cmp flag,0
	jne exit_
	mov eax,n
	inc eax
exit_:
	ret
AllDoubPalindroms1 endp

@AllDoubPalindroms2@8 proc ;c, a: dword, n:dword
	push ecx
	push ebx
	push edx
	mov flag,0
	xor eax,eax
	mov ebx,ecx
	mov ecx,edx
	jecxz end_
for_ :
	mov edx, [ebx]
	mov temp, edx
	push ebx
	call DoublePal
	pop ebx
	cmp res, 2
	jne continue_
	cmp flag, 0
	jne compare_
	mov eax,ebx
	mov flag, 1
	jmp continue_
compare_ :
	mov edx, [ebx]
	cmp [eax], edx
	jnl continue_
	mov eax,ebx
continue_ :
	add ebx, 4
	loop for_
end_:
	pop temp
	pop ebx
	pop ecx
	xor edx,edx
	sub eax,ecx
	shr eax,2
	mov edx,temp
	cmp flag,0
	jne exit_
	mov eax,edx
	inc eax
exit_:
	ret
@AllDoubPalindroms2@8 endp

DoublePal proc
	pushad
	mov eax, temp
	mul temp
	push temp
	mov temp, eax
	call IsPalindrom
	mov bl, res
	pop temp
	call IsPalindrom
	add res, bl
	popad
	ret
DoublePal endp

IsPalindrom proc
	pushad
	mov eax,temp
	mov ecx,10
	xor esi,esi
while_:
	cmp eax,0
	je end_
	xor edx,edx
	div ecx
	push eax
	push edx
	mov eax,esi
	mul ecx
	pop edx
	add eax,edx
	mov esi,eax
	pop eax
	jmp while_
end_:
	cmp temp,esi
	je yes_
	mov res,0
	jmp quit_
yes_:
	mov res,1
quit_:
	popad
	ret
IsPalindrom endp
	end