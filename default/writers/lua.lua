-- Exposed vars
-- content - string we write to
-- animation - read-only animation to be converted to appropriate format

content = 'return {\n'
content = content .. "\tname = '" .. animation:getName() .. "',\n"
content = content .. "\tspritesheet = '" .. animation:getSpritesheet() .. "',\n"
content = content .. "\tframes = {\n"
for _, v in pairs(animation:getFrames()) do
	content = content .. "\t{\n"
	content = content .. "\t\t" .. "name = '" .. v:getName() .. "',\n"
	content = content .. "\t\t" .. 'rect = {' .. v:getRect():x() .. ', ' .. v:getRect():y() .. ', ' .. v:getRect():w() .. ', ' .. v:getRect():h() .. '}\n'
	content = content .. "\t},\n"
end
content = content .. '\t}\n'
content = content .. '}'
