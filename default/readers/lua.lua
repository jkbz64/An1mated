-- Exposed vars
-- content - content of file as string
-- animation - animation which we 'write' to

local animationTable = loadstring(content)()
animation:setName(animationTable.name)
animation:setSpritesheet(animationTable.spritesheet)

if animationTable.frames ~= nil then
	for _, v in pairs(animationTable.frames) do
		animation:addFrame(v.name, v.rect[1], v.rect[2], v.rect[3], v.rect[4], v.delay)
	end
end
