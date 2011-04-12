class CreateDrivingStats < ActiveRecord::Migration
  def self.up
    create_table :driving_stats do |t|
      t.integer :id
      t.timestamp :iphone_timestamp
      t.string :iphone_udid
      t.float :velocity
      t.float :acceleration
      t.float :latitude
      t.float :longitude
      t.integer :num_redlights

      t.timestamps
    end
  end

  def self.down
    drop_table :driving_stats
  end
end
