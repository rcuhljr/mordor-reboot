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
    @filedata[@reference+@pointer-2,2].reverse.pack("C*").unpack('B*').first.to_i(2)
  end

  def readFloat()
    @pointer += 4
    @filedata[@reference+@pointer-4,4].pack("C*").unpack('f').first
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
  ahash = {}
  reader.seekTo(RECORD_LENGTH);
  ahash["name"] = reader.readVbString   
  ahash["min_stats"] = (0..5).map{|_| reader.readWord}
  padding = reader.readWord
  ahash["max_stats"] = (0..5).map{|_| reader.readWord}
  padding = reader.readWord
  ahash["resistances"] = (0..10).map{|_| reader.readWord}
  padding = reader.readWord  
  ahash["alignment"] = reader.readWord.to_s(2).rjust(3,"0").chars.map{|x| x == "1"}
  padding = reader.readWord
  ahash["size"] = reader.readWord
  ahash["bonuspoints"] = reader.readWord
  ahash["max_age"] = reader.readWord
  ahash["exp_factor"] = reader.readFloat
  puts ahash.to_json
  #puts "race: #{reader.readVbString}"
  #puts "min_stats: #{(0..5).map{|_| reader.readWord}}"
  #padding = reader.readWord
  #puts "max_stats: #{(0..5).map{|_| reader.readWord}}"
  #padding = reader.readWord
  #puts "resistances: #{(0..10).map{|_| reader.readWord}}"
  #padding = reader.readWord
  #puts "alignment: #{ reader.readWord }"
  #padding = reader.readWord
  #puts "size: #{ reader.readWord }"
  #puts "bonuspoints: #{ reader.readWord }"
  #puts "max_age: #{ reader.readWord }"
  #puts "expfactor: #{ reader.readFloat }"
end