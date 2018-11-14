function OnNewTurnStarted()
	local randomX = math.random(-1, 1)
	local randomY
	if (randomX == 0) then
		randomY = math.random(-1, 1)
	else
		randomY = 0
	end
	Logic.Move(Logic.this, randomX, randomY)
	return
end