require 'json'

RECORD_LENGTH = 260

class MdataReader
  def initialize(path)
    @filedata = IO.binread(path).bytes
    @pointer = 0
    @reference = 0
  end

  def readVbString()
    length = readWord
    @pointer += length
    @filedata [@reference+@pointer-length,length].map{|x| x.chr}.join
  end

  def readWord()
    @pointer += 2
    @filedata[@reference+@pointer-2,2].reverse.map{|x| x.to_s(2).rjust(8, "0")}.join.to_i(2)
  end

  def readFloat()
    @pointer += 4
    [@filedata[@reference+@pointer-4,4].map{|x| x.to_s(16).rjust(2, "0")}.join].pack("H*").unpack('f').first
  end

  def seekTo(target)    
    return false if(@pointer > target)    
    @pointer = 0
    @reference += target    
  end

end

reader = MdataReader.new("C:/code/data/Mdata1.mdr")

puts "version #{reader.readVbString}" 
reader.seekTo(RECORD_LENGTH);
race_count = reader.readWord
puts "number of races #{race_count}"
reader.seekTo(RECORD_LENGTH);
puts "number of guilds #{reader.readWord}"
reader.seekTo(RECORD_LENGTH);
puts "number of itemsubtypes #{reader.readWord}"
reader.seekTo(RECORD_LENGTH);
puts "number of itemtypes #{reader.readWord}"
reader.seekTo(RECORD_LENGTH);
puts "number of monstersubtypes #{reader.readWord}"
reader.seekTo(RECORD_LENGTH);
puts "number of monstertypes #{reader.readWord}"

race_count.times do |_|
  reader.seekTo(RECORD_LENGTH);
  puts "race: #{reader.readVbString}"
  puts "min_stats: #{(0..5).map{|_| reader.readWord}}"
  padding = reader.readWord
  puts "max_stats: #{(0..5).map{|_| reader.readWord}}"
  padding = reader.readWord
  puts "resistances: #{(0..10).map{|_| reader.readWord}}"
  padding = reader.readWord
  puts "alignment: #{ reader.readWord }"
  padding = reader.readWord
  puts "size: #{ reader.readWord }"
  puts "bonuspoints: #{ reader.readWord }"
  puts "max_age: #{ reader.readWord }"
  puts "expfactor: #{ reader.readFloat }"
end