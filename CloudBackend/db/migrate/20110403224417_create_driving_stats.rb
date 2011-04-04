class CreateDrivingStats < ActiveRecord::Migration
  def self.up
    create_table :driving_stats do |t|
      t.int :id
      t.Date :timestamp
      t.float :velocity
      t.float :acceleration
      t.float :latitude
      t.float :longitude
      t.int :num_redlights

      t.timestamps
    end
  end

  def self.down
    drop_table :driving_stats
  end
end
