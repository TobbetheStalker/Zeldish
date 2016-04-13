function fib (var1)
	lastNum = 0
	thisNum = 1
	print(0)
	print(1)
	for i = 2, var1, 1
	do
		print(lastNum + thisNum);
		temp = thisNum
		thisNum = lastNum + thisNum
		lastNum = temp
	end
end

nrOfRuns = 0

function date ()
	nrOfRuns = nrOfRuns + 1
	output = os.date() .. "\n  Times called: " .. nrOfRuns
	return output
end