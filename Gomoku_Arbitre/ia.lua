function search(mapp, new_map, x2, y2, xplus, yplus)
   local n = 0
   while (x2 + xplus >= 1 and y2 + yplus >= 1 and y2 + yplus >= 1 and y2 + yplus <= 8 and mapp[y2 + yplus][x2 + xplus] == 1) do
      n = n + 1
      if (xplus > 0) then
	 xplus = xplus + 1
      elseif (xplus < 0) then
	 xplus = xplus - 1
      end
      if (yplus > 0) then
	 yplus = yplus + 1
      elseif (yplus < 0) then
	 yplus = yplus - 1
      end
   end
   if (x2 + xplus >= 1 and x2 + xplus <= 8 and y2 + yplus >= 1 and y2 + yplus <= 8) then
      new_map[y2 + yplus][x2 + xplus] = new_map[y2 + yplus][x2 + xplus] + n
   end
   return new_map
end

-- Envoyer la map contenant les pions
function ia(mapp)
   local new_map = {}
   for i = 1, #mapp do
      new_map[i] = {}
      for j = 1, #mapp[i] do
	 new_map[i][j] = 0
      end
   end
   local x = 1
   local y = 1
   local x2 = 1
   local y2 = 1
   while (y <= 8) do
      while (x <= 8) do
	 if (mapp[y][x] == 2) then
	    x2 = x
	    y2 = y
	    new_map = search(mapp, new_map, x2, y2, -1, 0)
	    new_map = search(mapp, new_map, x2, y2, -1, -1)
	    new_map = search(mapp, new_map, x2, y2, 0, -1)
	    new_map = search(mapp, new_map, x2, y2, 1, -1)
	    new_map = search(mapp, new_map, x2, y2, 1, 0)
	    new_map = search(mapp, new_map, x2, y2, 1, 1)
	    new_map = search(mapp, new_map, x2, y2, 0, 1)
	    new_map = search(mapp, new_map, x2, y2, -1, 1)
	 end
	 x = x + 1
      end
      x = 0
      y = y + 1
   end
   local line = 0
   local char = 0
   local dict = {}
   for y, line in ipairs(new_map) do
      for x, char in ipairs(line) do
	 if (dict[char + 1] == nil) then
	    dict[char + 1] = {}
	 end
	 table.insert(dict[char + 1], {x, y})
      end
   end
   for i = #dict, 1, -1 do
      for j = #dict[i], 1, -1 do
	 -- Appeler l'arbitre avec dict[i][j][1] (x) et dict[i][j][2] (y)
	 -- Si c'est bon, return pour finir la fonction
	 -- Sinon laisser continuer
      end
   end
end
